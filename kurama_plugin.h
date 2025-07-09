#ifndef KURAMA_PLUGIN_H
#define KURAMA_PLUGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLUGIN_NAME 64
#define MAX_PLUGIN_DESC 256
#define MAX_PLUGINS 10

// Plugin types
typedef enum {
    PLUGIN_PERSONALITY,
    PLUGIN_LANGUAGE,
    PLUGIN_EMOTION,
    PLUGIN_LEARNING,
    PLUGIN_CREATIVITY,
    PLUGIN_ANALYSIS
} PluginType;

// Plugin function pointer types
typedef char* (*plugin_process_func)(const char* input);
typedef int (*plugin_init_func)(void);
typedef void (*plugin_cleanup_func)(void);

// Individual plugin structure
typedef struct {
    char name[MAX_PLUGIN_NAME];
    char description[MAX_PLUGIN_DESC];
    PluginType type;
    int is_active;
    int priority;
    plugin_init_func init;
    plugin_process_func process;
    plugin_cleanup_func cleanup;
    void* plugin_data;
} Plugin;

// Plugin system structure
typedef struct {
    Plugin plugins[MAX_PLUGINS];
    int count;
    int total_loaded;
    int active_count;
} PluginSystem;

// Plugin function declarations
int plugin_system_init(PluginSystem *sys);
void plugin_system_shutdown(PluginSystem *sys);
int plugin_load(PluginSystem *sys, const char* name, const char* desc, PluginType type);
int plugin_activate(PluginSystem *sys, const char* name);
int plugin_deactivate(PluginSystem *sys, const char* name);
char* plugin_process_input(PluginSystem *sys, const char* input, PluginType type);
void plugin_list_all(const PluginSystem *sys);
Plugin* plugin_find_by_name(PluginSystem *sys, const char* name);
void plugin_load_defaults(PluginSystem *sys);

// Built-in plugin processors
char* personality_plugin_process(const char* input);
char* emotion_plugin_process(const char* input);
char* creativity_plugin_process(const char* input);
char* learning_plugin_process(const char* input);

#endif // KURAMA_PLUGIN_H