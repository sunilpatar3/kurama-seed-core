#include "kurama_memory.h"

// Memory type names for debugging
static const char* memory_type_names[] = {
    "Conversation", "Learned Fact", "Emotional State", "Pattern", "Evolution"
};

int memory_init(MemorySystem *mem_sys) {
    if (!mem_sys) return 0;
    
    mem_sys->memories = malloc(INITIAL_MEMORY_CAPACITY * sizeof(Memory));
    if (!mem_sys->memories) {
        fprintf(stderr, "Failed to allocate initial memory\n");
        return 0;
    }
    
    mem_sys->count = 0;
    mem_sys->capacity = INITIAL_MEMORY_CAPACITY;
    mem_sys->total_saved = 0;
    mem_sys->total_recalled = 0;
    
    printf("💾 Memory system initialized (capacity: %d)\n", mem_sys->capacity);
    return 1;
}

void memory_shutdown(MemorySystem *mem_sys) {
    if (!mem_sys || !mem_sys->memories) return;
    
    printf("💾 Saving %d memories before shutdown...\n", mem_sys->count);
    
    // In a real implementation, you might save to disk here
    
    free(mem_sys->memories);
    mem_sys->memories = NULL;
    mem_sys->count = 0;
    mem_sys->capacity = 0;
    
    printf("💾 Memory system shutdown complete.\n");
}

int memory_save(MemorySystem *mem_sys, const char* text, const char* tag, MemoryType type, int importance) {
    if (!mem_sys || !text || !tag) return 0;
    
    // Resize if necessary
    if (mem_sys->count >= mem_sys->capacity) {
        if (!memory_resize(mem_sys)) {
            fprintf(stderr, "Failed to resize memory system\n");
            return 0;
        }
    }
    
    Memory *new_memory = &mem_sys->memories[mem_sys->count];
    
    // Copy data
    strncpy(new_memory->text, text, MAX_MEMORY_TEXT - 1);
    new_memory->text[MAX_MEMORY_TEXT - 1] = '\0';
    
    strncpy(new_memory->tag, tag, MAX_MEMORY_TAG - 1);
    new_memory->tag[MAX_MEMORY_TAG - 1] = '\0';
    
    new_memory->type = type;
    new_memory->timestamp = time(NULL);
    new_memory->importance_score = importance;
    new_memory->access_count = 0;
    
    mem_sys->count++;
    mem_sys->total_saved++;
    
    printf("💾 Memory saved [%s]: %.50s%s\n", 
           memory_type_names[type], 
           text, 
           strlen(text) > 50 ? "..." : "");
    
    return 1;
}

Memory* memory_recall_by_tag(MemorySystem *mem_sys, const char* tag) {
    if (!mem_sys || !tag) return NULL;
    
    for (int i = 0; i < mem_sys->count; i++) {
        if (strcmp(mem_sys->memories[i].tag, tag) == 0) {
            mem_sys->memories[i].access_count++;
            mem_sys->total_recalled++;
            
            printf("🔍 Memory recalled by tag '%s': %.50s%s\n", 
                   tag, 
                   mem_sys->memories[i].text,
                   strlen(mem_sys->memories[i].text) > 50 ? "..." : "");
            
            return &mem_sys->memories[i];
        }
    }
    
    printf("🔍 No memory found with tag '%s'\n", tag);
    return NULL;
}

Memory* memory_recall_by_type(MemorySystem *mem_sys, MemoryType type) {
    if (!mem_sys) return NULL;
    
    // Find the most recent memory of this type
    Memory *found = NULL;
    time_t latest_time = 0;
    
    for (int i = 0; i < mem_sys->count; i++) {
        if (mem_sys->memories[i].type == type) {
            if (mem_sys->memories[i].timestamp > latest_time) {
                latest_time = mem_sys->memories[i].timestamp;
                found = &mem_sys->memories[i];
            }
        }
    }
    
    if (found) {
        found->access_count++;
        mem_sys->total_recalled++;
        
        printf("🔍 Memory recalled by type '%s': %.50s%s\n", 
               memory_type_names[type], 
               found->text,
               strlen(found->text) > 50 ? "..." : "");
    } else {
        printf("🔍 No memory found of type '%s'\n", memory_type_names[type]);
    }
    
    return found;
}

Memory* memory_recall_recent(MemorySystem *mem_sys, int count) {
    if (!mem_sys || count <= 0) return NULL;
    
    if (count > mem_sys->count) count = mem_sys->count;
    
    printf("🔍 Recalling %d most recent memories:\n", count);
    
    // Return pointer to the last 'count' memories
    // In a real implementation, you might want to return a dynamically allocated array
    for (int i = mem_sys->count - count; i < mem_sys->count; i++) {
        if (i >= 0) {
            mem_sys->memories[i].access_count++;
            printf("  [%d] %s: %.50s%s\n", 
                   i, 
                   memory_type_names[mem_sys->memories[i].type],
                   mem_sys->memories[i].text,
                   strlen(mem_sys->memories[i].text) > 50 ? "..." : "");
        }
    }
    
    mem_sys->total_recalled += count;
    
    return (count > 0 && mem_sys->count > 0) ? &mem_sys->memories[mem_sys->count - count] : NULL;
}

int memory_delete_by_tag(MemorySystem *mem_sys, const char* tag) {
    if (!mem_sys || !tag) return 0;
    
    for (int i = 0; i < mem_sys->count; i++) {
        if (strcmp(mem_sys->memories[i].tag, tag) == 0) {
            // Shift all memories after this one down
            for (int j = i; j < mem_sys->count - 1; j++) {
                mem_sys->memories[j] = mem_sys->memories[j + 1];
            }
            mem_sys->count--;
            
            printf("🗑️ Memory deleted with tag '%s'\n", tag);
            return 1;
        }
    }
    
    printf("🗑️ No memory found with tag '%s' to delete\n", tag);
    return 0;
}

void memory_cleanup_old(MemorySystem *mem_sys, int max_age_seconds) {
    if (!mem_sys) return;
    
    time_t current_time = time(NULL);
    int deleted_count = 0;
    
    for (int i = 0; i < mem_sys->count; i++) {
        if (current_time - mem_sys->memories[i].timestamp > max_age_seconds) {
            // Delete this memory by shifting others down
            for (int j = i; j < mem_sys->count - 1; j++) {
                mem_sys->memories[j] = mem_sys->memories[j + 1];
            }
            mem_sys->count--;
            deleted_count++;
            i--; // Check this index again since we shifted
        }
    }
    
    if (deleted_count > 0) {
        printf("🧹 Cleaned up %d old memories (older than %d seconds)\n", 
               deleted_count, max_age_seconds);
    }
}

void memory_print_stats(const MemorySystem *mem_sys) {
    if (!mem_sys) return;
    
    printf("\n═══ MEMORY STATISTICS ═══\n");
    printf("📊 Total Memories: %d/%d\n", mem_sys->count, mem_sys->capacity);
    printf("💾 Total Saved: %d\n", mem_sys->total_saved);
    printf("🔍 Total Recalled: %d\n", mem_sys->total_recalled);
    
    // Count by type
    int type_counts[5] = {0};
    for (int i = 0; i < mem_sys->count; i++) {
        if (mem_sys->memories[i].type < 5) {
            type_counts[mem_sys->memories[i].type]++;
        }
    }
    
    printf("📋 Memory Types:\n");
    for (int i = 0; i < 5; i++) {
        if (type_counts[i] > 0) {
            printf("  - %s: %d\n", memory_type_names[i], type_counts[i]);
        }
    }
    
    // Memory usage
    double usage_percent = (double)mem_sys->count / mem_sys->capacity * 100.0;
    printf("📈 Memory Usage: %.1f%%\n", usage_percent);
    
    printf("══════════════════════════\n\n");
}

void memory_print_all(const MemorySystem *mem_sys) {
    if (!mem_sys) return;
    
    printf("\n═══ ALL MEMORIES (%d) ═══\n", mem_sys->count);
    
    for (int i = 0; i < mem_sys->count; i++) {
        char time_str[64];
        struct tm *tm_info = localtime(&mem_sys->memories[i].timestamp);
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);
        
        printf("[%d] %s (%s) [%s] (accessed %d times, importance %d)\n",
               i,
               mem_sys->memories[i].tag,
               memory_type_names[mem_sys->memories[i].type],
               time_str,
               mem_sys->memories[i].access_count,
               mem_sys->memories[i].importance_score);
        printf("    \"%s\"\n\n", mem_sys->memories[i].text);
    }
    
    printf("═══════════════════════════\n\n");
}

int memory_resize(MemorySystem *mem_sys) {
    if (!mem_sys) return 0;
    
    int new_capacity = mem_sys->capacity * 2;
    Memory *new_memories = realloc(mem_sys->memories, new_capacity * sizeof(Memory));
    
    if (!new_memories) {
        fprintf(stderr, "Failed to resize memory system\n");
        return 0;
    }
    
    mem_sys->memories = new_memories;
    mem_sys->capacity = new_capacity;
    
    printf("💾 Memory system resized to capacity %d\n", new_capacity);
    return 1;
}