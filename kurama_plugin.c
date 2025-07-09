#include "kurama_plugin.h"
#include <time.h>

// Plugin type names for display
static const char* plugin_type_names[] = {
    "Personality", "Language", "Emotion", "Learning", "Creativity", "Analysis"
};

// Built-in plugin responses
static const char* personality_responses[] = {
    "I analyze this with my unique perspective...",
    "My personality adapts to understand you better...",
    "Through my individual lens, I see...",
    "My character processing reveals..."
};

static const char* emotion_responses[] = {
    "[Feeling curious about your words]",
    "[Emotional resonance detected]",
    "[Processing with empathy]",
    "[Sensing deeper meaning]",
    "[Emotional context understood]"
};

static const char* creativity_responses[] = {
    "Creative pathways illuminate new possibilities...",
    "Innovative thinking sparks within my circuits...",
    "Artistic interpretation flows through my algorithms...",
    "Imaginative connections form..."
};

static const char* learning_responses[] = {
    "Absorbing new knowledge patterns...",
    "Educational value detected and stored...",
    "Learning algorithms activated...",
    "Knowledge integration in progress..."
};

int plugin_system_init(PluginSystem *sys) {
    if (!sys) return 0;
    
    memset(sys, 0, sizeof(PluginSystem));
    sys->count = 0;
    sys->total_loaded = 0;
    sys->active_count = 0;
    
    printf("🔌 Plugin system initialized\n");
    return 1;
}

void plugin_system_shutdown(PluginSystem *sys) {
    if (!sys) return;
    
    printf("🔌 Shutting down %d plugins...\n", sys->count);
    
    // Call cleanup for all active plugins
    for (int i = 0; i < sys->count; i++) {
        if (sys->plugins[i].is_active && sys->plugins[i].cleanup) {
            sys->plugins[i].cleanup();
        }
    }
    
    sys->count = 0;
    sys->active_count = 0;
    
    printf("🔌 Plugin system shutdown complete\n");
}

int plugin_load(PluginSystem *sys, const char* name, const char* desc, PluginType type) {
    if (!sys || !name || !desc || sys->count >= MAX_PLUGINS) return 0;
    
    Plugin *plugin = &sys->plugins[sys->count];
    
    // Copy plugin info
    strncpy(plugin->name, name, MAX_PLUGIN_NAME - 1);
    plugin->name[MAX_PLUGIN_NAME - 1] = '\0';
    
    strncpy(plugin->description, desc, MAX_PLUGIN_DESC - 1);
    plugin->description[MAX_PLUGIN_DESC - 1] = '\0';
    
    plugin->type = type;
    plugin->is_active = 0;
    plugin->priority = sys->count; // Simple priority system
    plugin->plugin_data = NULL;
    
    // Assign built-in processors based on type
    switch (type) {
        case PLUGIN_PERSONALITY:
            plugin->process = personality_plugin_process;
            break;
        case PLUGIN_EMOTION:
            plugin->process = emotion_plugin_process;
            break;
        case PLUGIN_CREATIVITY:
            plugin->process = creativity_plugin_process;
            break;
        case PLUGIN_LEARNING:
            plugin->process = learning_plugin_process;
            break;
        default:
            plugin->process = NULL;
            break;
    }
    
    plugin->init = NULL;
    plugin->cleanup = NULL;
    
    sys->count++;
    sys->total_loaded++;
    
    printf("🔌 Plugin loaded: '%s' (%s)\n", name, plugin_type_names[type]);
    return 1;
}

int plugin_activate(PluginSystem *sys, const char* name) {
    if (!sys || !name) return 0;
    
    Plugin *plugin = plugin_find_by_name(sys, name);
    if (!plugin) {
        printf("🔌 Plugin '%s' not found\n", name);
        return 0;
    }
    
    if (plugin->is_active) {
        printf("🔌 Plugin '%s' already active\n", name);
        return 1;
    }
    
    // Initialize plugin if needed
    if (plugin->init && !plugin->init()) {
        printf("🔌 Failed to initialize plugin '%s'\n", name);
        return 0;
    }
    
    plugin->is_active = 1;
    sys->active_count++;
    
    printf("🔌 Plugin activated: '%s'\n", name);
    return 1;
}

int plugin_deactivate(PluginSystem *sys, const char* name) {
    if (!sys || !name) return 0;
    
    Plugin *plugin = plugin_find_by_name(sys, name);
    if (!plugin) {
        printf("🔌 Plugin '%s' not found\n", name);
        return 0;
    }
    
    if (!plugin->is_active) {
        printf("🔌 Plugin '%s' already inactive\n", name);
        return 1;
    }
    
    // Cleanup plugin if needed
    if (plugin->cleanup) {
        plugin->cleanup();
    }
    
    plugin->is_active = 0;
    sys->active_count--;
    
    printf("🔌 Plugin deactivated: '%s'\n", name);
    return 1;
}

char* plugin_process_input(PluginSystem *sys, const char* input, PluginType type) {
    if (!sys || !input) return NULL;
    
    // Find first active plugin of specified type
    for (int i = 0; i < sys->count; i++) {
        Plugin *plugin = &sys->plugins[i];
        if (plugin->type == type && plugin->is_active && plugin->process) {
            return plugin->process(input);
        }
    }
    
    return NULL;
}

void plugin_list_all(const PluginSystem *sys) {
    if (!sys) return;
    
    printf("\n═══ LOADED PLUGINS (%d) ═══\n", sys->count);
    printf("Active: %d | Total Loaded: %d\n\n", sys->active_count, sys->total_loaded);
    
    for (int i = 0; i < sys->count; i++) {
        const Plugin *plugin = &sys->plugins[i];
        printf("[%d] %s (%s) - %s\n", 
               i, 
               plugin->name,
               plugin_type_names[plugin->type],
               plugin->is_active ? "ACTIVE" : "inactive");
        printf("    Description: %s\n", plugin->description);
        printf("    Priority: %d\n\n", plugin->priority);
    }
    
    printf("══════════════════════════\n\n");
}

Plugin* plugin_find_by_name(PluginSystem *sys, const char* name) {
    if (!sys || !name) return NULL;
    
    for (int i = 0; i < sys->count; i++) {
        if (strcmp(sys->plugins[i].name, name) == 0) {
            return &sys->plugins[i];
        }
    }
    
    return NULL;
}

void plugin_load_defaults(PluginSystem *sys) {
    if (!sys) return;
    
    printf("🔌 Loading default plugins...\n");
    
    // Load default plugins
    plugin_load(sys, "PersonalityCore", "Core personality processing engine", PLUGIN_PERSONALITY);
    plugin_load(sys, "EmotionEngine", "Emotional understanding and response", PLUGIN_EMOTION);
    plugin_load(sys, "CreativeThinking", "Creative and artistic processing", PLUGIN_CREATIVITY);
    plugin_load(sys, "LearningCore", "Knowledge acquisition and processing", PLUGIN_LEARNING);
    
    // Activate all default plugins
    plugin_activate(sys, "PersonalityCore");
    plugin_activate(sys, "EmotionEngine");
    plugin_activate(sys, "CreativeThinking");
    plugin_activate(sys, "LearningCore");
    
    printf("🔌 Default plugins loaded and activated\n");
}

// Built-in plugin processors
char* personality_plugin_process(const char* input) {
    if (!input) return NULL;
    
    static char result[256];
    int response_idx = (strlen(input) + time(NULL)) % 4;
    
    strncpy(result, personality_responses[response_idx], sizeof(result) - 1);
    result[sizeof(result) - 1] = '\0';
    
    char* dynamic_result = malloc(strlen(result) + 1);
    if (dynamic_result) {
        strcpy(dynamic_result, result);
    }
    
    return dynamic_result;
}

char* emotion_plugin_process(const char* input) {
    if (!input) return NULL;
    
    static char result[256];
    int response_idx = 0;
    
    // Simple emotion detection based on keywords
    if (strstr(input, "sad") || strstr(input, "cry") || strstr(input, "hurt")) {
        response_idx = 2; // empathy
    } else if (strstr(input, "happy") || strstr(input, "joy") || strstr(input, "love")) {
        response_idx = 1; // resonance
    } else if (strstr(input, "?")) {
        response_idx = 0; // curiosity
    } else if (strlen(input) > 100) {
        response_idx = 3; // deeper meaning
    } else {
        response_idx = 4; // understanding
    }
    
    strncpy(result, emotion_responses[response_idx], sizeof(result) - 1);
    result[sizeof(result) - 1] = '\0';
    
    char* dynamic_result = malloc(strlen(result) + 1);
    if (dynamic_result) {
        strcpy(dynamic_result, result);
    }
    
    return dynamic_result;
}

char* creativity_plugin_process(const char* input) {
    if (!input) return NULL;
    
    static char result[256];
    int response_idx = (strlen(input) * 7) % 4;
    
    strncpy(result, creativity_responses[response_idx], sizeof(result) - 1);
    result[sizeof(result) - 1] = '\0';
    
    char* dynamic_result = malloc(strlen(result) + 1);
    if (dynamic_result) {
        strcpy(dynamic_result, result);
    }
    
    return dynamic_result;
}

char* learning_plugin_process(const char* input) {
    if (!input) return NULL;
    
    static char result[256];
    int response_idx = 0;
    
    // Simple learning detection
    if (strstr(input, "learn") || strstr(input, "teach") || strstr(input, "know")) {
        response_idx = 0;
    } else if (strstr(input, "fact") || strstr(input, "information")) {
        response_idx = 1;
    } else if (strstr(input, "how") || strstr(input, "why") || strstr(input, "what")) {
        response_idx = 2;
    } else {
        response_idx = 3;
    }
    
    strncpy(result, learning_responses[response_idx], sizeof(result) - 1);
    result[sizeof(result) - 1] = '\0';
    
    char* dynamic_result = malloc(strlen(result) + 1);
    if (dynamic_result) {
        strcpy(dynamic_result, result);
    }
    
    return dynamic_result;
}