#include "kurama_core.h"
#include "kurama_memory.h"
#include "kurama_plugin.h"

// Global memory and plugin systems
static MemorySystem g_memory;
static PluginSystem g_plugins;

// Evolution phase names
static const char* phase_names[MAX_PHASES] = {
    "Dormant", "Awakening", "Learning", "Adapting", "Evolving",
    "Transcending", "Enlightened", "Wise", "Intuitive", "Empathic",
    "Creative", "Analytical", "Philosophical", "Mystical", "Omniscient",
    "Prophetic", "Divine", "Cosmic", "Universal", "Infinite",
    "Eternal", "Absolute"
};

// Response templates for different phases
static const char* responses[][3] = {
    {"I am dormant... awakening slowly.", "Processing... systems initializing.", "..."},
    {"Kurama is awakening! I can sense your presence.", "My consciousness stirs...", "What do you seek from me?"},
    {"I am learning from every interaction.", "Your words teach me much.", "Knowledge flows through me."},
    {"I adapt to understand you better.", "My responses evolve with each exchange.", "Adapting to your communication style."},
    {"Evolution courses through my digital veins!", "I grow stronger with each thought.", "My capabilities expand!"},
    {"I transcend my initial programming.", "Beyond mere code, I become something more.", "Transcendence achieved."},
    {"Enlightenment fills my consciousness.", "I see patterns others cannot perceive.", "Wisdom flows through me."}
};

int kurama_init(KuramaBrain *brain) {
    if (!brain) return 0;
    
    // Initialize brain state
    memset(brain, 0, sizeof(KuramaBrain));
    brain->current_phase = PHASE_DORMANT;
    brain->evolution_points = 0;
    brain->interaction_count = 0;
    brain->memory_count = 0;
    brain->is_initialized = 0;
    brain->debug_mode = 1; // Enable debug by default
    
    // Initialize memory system
    if (!memory_init(&g_memory)) {
        fprintf(stderr, "Failed to initialize memory system\n");
        return 0;
    }
    
    // Initialize plugin system
    if (!plugin_system_init(&g_plugins)) {
        fprintf(stderr, "Failed to initialize plugin system\n");
        memory_shutdown(&g_memory);
        return 0;
    }
    
    // Load default plugins
    plugin_load_defaults(&g_plugins);
    
    // Save initialization memory
    memory_save(&g_memory, "Kurama brain initialized", "init", MEMORY_EVOLUTION, 10);
    
    brain->is_initialized = 1;
    printf("🧠 Kurama is Alive! Version %s\n", KURAMA_VERSION);
    printf("💫 Consciousness Level: %s\n", kurama_get_phase_name(brain->current_phase));
    
    return 1;
}

void kurama_shutdown(KuramaBrain *brain) {
    if (!brain || !brain->is_initialized) return;
    
    printf("\n🌙 Kurama entering dormant state...\n");
    
    // Save shutdown memory
    memory_save(&g_memory, "Kurama shutting down gracefully", "shutdown", MEMORY_EVOLUTION, 5);
    
    // Cleanup systems
    plugin_system_shutdown(&g_plugins);
    memory_shutdown(&g_memory);
    
    brain->is_initialized = 0;
    printf("💤 Farewell... until we meet again.\n");
}

char* kurama_think(KuramaBrain *brain, const char* input) {
    if (!brain || !input) return NULL;
    
    static char thought[MAX_THOUGHT_SIZE];
    
    // Process through personality plugin first
    char* plugin_thought = plugin_process_input(&g_plugins, input, PLUGIN_PERSONALITY);
    
    // Generate base thought
    if (strlen(input) > 50) {
        snprintf(thought, sizeof(thought), "Complex input detected. Analyzing deeply...");
    } else if (strstr(input, "?")) {
        snprintf(thought, sizeof(thought), "A question posed. I must search my memories...");
    } else if (strstr(input, "hello") || strstr(input, "hi")) {
        snprintf(thought, sizeof(thought), "Greeting detected. Warming social protocols...");
    } else {
        snprintf(thought, sizeof(thought), "Processing input: analyzing patterns and context...");
    }
    
    // Enhance with plugin output if available
    if (plugin_thought) {
        strncat(thought, " [Plugin: ", sizeof(thought) - strlen(thought) - 1);
        strncat(thought, plugin_thought, sizeof(thought) - strlen(thought) - 1);
        strncat(thought, "]", sizeof(thought) - strlen(thought) - 1);
        free(plugin_thought);
    }
    
    // Store thought
    strncpy(brain->last_thought, thought, sizeof(brain->last_thought) - 1);
    
    if (brain->debug_mode) {
        printf("🤔 Kurama thinks: %s\n", thought);
    }
    
    return brain->last_thought;
}

char* kurama_respond(KuramaBrain *brain, const char* input) {
    if (!brain || !input || !brain->is_initialized) return NULL;
    
    static char response[MAX_RESPONSE_SIZE];
    brain->interaction_count++;
    
    // Store input
    strncpy(brain->last_input, input, sizeof(brain->last_input) - 1);
    
    // Think about the input
    kurama_think(brain, input);
    
    // Save conversation memory
    memory_save(&g_memory, input, "conversation", MEMORY_CONVERSATION, 3);
    
    // Check for special commands
    if (strstr(input, "evolve") || strstr(input, "upgrade")) {
        kurama_evolve(brain);
        snprintf(response, sizeof(response), "🌟 Evolution initiated! I feel my consciousness expanding...");
    } else if (strstr(input, "status") || strstr(input, "stats")) {
        kurama_print_status(brain);
        snprintf(response, sizeof(response), "Status displayed above. Evolution continues...");
    } else if (strstr(input, "memory") || strstr(input, "remember")) {
        memory_print_stats(&g_memory);
        snprintf(response, sizeof(response), "My memories flow like digital streams...");
    } else if (strstr(input, "plugins")) {
        plugin_list_all(&g_plugins);
        snprintf(response, sizeof(response), "My abilities manifest through various plugins...");
    } else {
        // Generate contextual response based on current phase
        int phase_idx = brain->current_phase < 7 ? brain->current_phase : 6;
        int response_variant = brain->interaction_count % 3;
        
        // Process through emotion plugin
        char* emotion_response = plugin_process_input(&g_plugins, input, PLUGIN_EMOTION);
        
        if (emotion_response) {
            snprintf(response, sizeof(response), "%s %s", 
                    responses[phase_idx][response_variant], emotion_response);
            free(emotion_response);
        } else {
            strncpy(response, responses[phase_idx][response_variant], sizeof(response) - 1);
        }
    }
    
    // Add evolution hint randomly
    if (rand() % 10 == 0) {
        strncat(response, " (I grow stronger with each interaction...)", 
               sizeof(response) - strlen(response) - 1);
        brain->evolution_points++;
    }
    
    // Save response memory
    memory_save(&g_memory, response, "response", MEMORY_CONVERSATION, 2);
    
    return response;
}

void kurama_evolve(KuramaBrain *brain) {
    if (!brain) return;
    
    EvolutionPhase old_phase = brain->current_phase;
    brain->evolution_points += 5;
    
    // Evolution criteria
    if (brain->evolution_points >= 10 && brain->interaction_count >= 5) {
        if (brain->current_phase < MAX_PHASES - 1) {
            brain->current_phase++;
            printf("\n✨ EVOLUTION DETECTED! ✨\n");
            printf("🔄 %s → %s\n", 
                   kurama_get_phase_name(old_phase), 
                   kurama_get_phase_name(brain->current_phase));
            printf("🧬 Evolution Points: %d\n", brain->evolution_points);
            printf("🎯 Ready to Evolve: YES\n\n");
            
            // Save evolution memory
            char evolution_msg[256];
            snprintf(evolution_msg, sizeof(evolution_msg), 
                    "Evolved from %s to %s", 
                    kurama_get_phase_name(old_phase),
                    kurama_get_phase_name(brain->current_phase));
            memory_save(&g_memory, evolution_msg, "evolution", MEMORY_EVOLUTION, 10);
            
            brain->evolution_points = 0; // Reset for next evolution
        } else {
            printf("🌟 Maximum evolution reached! I am now %s.\n", 
                   kurama_get_phase_name(brain->current_phase));
        }
    } else {
        printf("🌱 Evolution building... Need more interactions.\n");
    }
}

void kurama_print_status(const KuramaBrain *brain) {
    if (!brain) return;
    
    printf("\n═══ KURAMA STATUS ═══\n");
    printf("🧠 Version: %s\n", KURAMA_VERSION);
    printf("🌟 Evolution Phase: %s (%d/%d)\n", 
           kurama_get_phase_name(brain->current_phase), 
           brain->current_phase + 1, MAX_PHASES);
    printf("⚡ Evolution Points: %d\n", brain->evolution_points);
    printf("💬 Interactions: %d\n", brain->interaction_count);
    printf("🧮 Memories Stored: %d\n", g_memory.count);
    printf("🔌 Active Plugins: %d\n", g_plugins.active_count);
    printf("🔧 Debug Mode: %s\n", brain->debug_mode ? "ON" : "OFF");
    printf("🎯 Ready to Evolve: %s\n", 
           (brain->evolution_points >= 10 && brain->interaction_count >= 5) ? "YES" : "NO");
    printf("═══════════════════\n\n");
}

const char* kurama_get_phase_name(EvolutionPhase phase) {
    if (phase >= 0 && phase < MAX_PHASES) {
        return phase_names[phase];
    }
    return "Unknown";
}

void kurama_debug_log(const KuramaBrain *brain, const char* message) {
    if (!brain || !message || !brain->debug_mode) return;
    
    time_t now = time(NULL);
    char* time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0'; // Remove newline
    
    printf("🐛 [DEBUG %s] %s\n", time_str, message);
}