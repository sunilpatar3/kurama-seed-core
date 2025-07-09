#ifndef KURAMA_MEMORY_H
#define KURAMA_MEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEMORY_TEXT 512
#define MAX_MEMORY_TAG 64
#define INITIAL_MEMORY_CAPACITY 10

// Memory types
typedef enum {
    MEMORY_CONVERSATION,
    MEMORY_LEARNED_FACT,
    MEMORY_EMOTIONAL_STATE,
    MEMORY_PATTERN,
    MEMORY_EVOLUTION
} MemoryType;

// Individual memory structure
typedef struct {
    char text[MAX_MEMORY_TEXT];
    char tag[MAX_MEMORY_TAG];
    MemoryType type;
    time_t timestamp;
    int importance_score;
    int access_count;
} Memory;

// Memory system structure
typedef struct {
    Memory *memories;
    int count;
    int capacity;
    int total_saved;
    int total_recalled;
} MemorySystem;

// Memory function declarations
int memory_init(MemorySystem *mem_sys);
void memory_shutdown(MemorySystem *mem_sys);
int memory_save(MemorySystem *mem_sys, const char* text, const char* tag, MemoryType type, int importance);
Memory* memory_recall_by_tag(MemorySystem *mem_sys, const char* tag);
Memory* memory_recall_by_type(MemorySystem *mem_sys, MemoryType type);
Memory* memory_recall_recent(MemorySystem *mem_sys, int count);
int memory_delete_by_tag(MemorySystem *mem_sys, const char* tag);
void memory_cleanup_old(MemorySystem *mem_sys, int max_age_seconds);
void memory_print_stats(const MemorySystem *mem_sys);
void memory_print_all(const MemorySystem *mem_sys);
int memory_resize(MemorySystem *mem_sys);

#endif // KURAMA_MEMORY_H