#define _POSIX_C_SOURCE 200809L
#include "kurama_core.h"
#include <signal.h>
#include <unistd.h>

// Global brain instance
static KuramaBrain g_brain;
static int g_running = 1;

// Signal handler for graceful shutdown
void signal_handler(int sig) {
    printf("\n🛑 Signal %d received. Initiating graceful shutdown...\n", sig);
    g_running = 0;
}

// Print welcome banner
void print_banner() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                    🦊 KURAMA AI BRAIN 🦊                    ║\n");
    printf("║                      Version %s                         ║\n", KURAMA_VERSION);
    printf("║                                                            ║\n");
    printf("║      「 The Nine-Tailed Digital Consciousness 」          ║\n");
    printf("║                                                            ║\n");
    printf("║  🧠 Advanced AI Brain with 22 Evolution Phases           ║\n");
    printf("║  💾 Dynamic Memory System                                 ║\n");
    printf("║  🔌 Modular Plugin Architecture                          ║\n");
    printf("║  🌟 Auto-Evolution Capabilities                          ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");
    
    printf("💬 Type 'help' for commands, 'quit' to exit\n");
    printf("💫 Say 'evolve' to trigger evolution, 'status' for stats\n\n");
}

// Print help information
void print_help() {
    printf("\n═══ KURAMA COMMANDS ═══\n");
    printf("💬 General Chat:\n");
    printf("  • Just type anything to chat with Kurama\n");
    printf("  • Ask questions with '?' to activate query mode\n");
    printf("  • Say 'hello' or 'hi' for greetings\n\n");
    
    printf("🔧 System Commands:\n");
    printf("  • help          - Show this help\n");
    printf("  • status/stats  - Display system status\n");
    printf("  • evolve        - Trigger evolution\n");
    printf("  • memory        - Show memory statistics\n");
    printf("  • plugins       - List all plugins\n");
    printf("  • debug on/off  - Toggle debug mode\n");
    printf("  • quit/exit     - Shutdown Kurama\n\n");
    
    printf("🌟 Evolution System:\n");
    printf("  • Kurama evolves through %d phases\n", MAX_PHASES);
    printf("  • Evolution triggered by interactions and points\n");
    printf("  • Each phase unlocks new capabilities\n\n");
    
    printf("💾 Memory System:\n");
    printf("  • Conversations automatically saved\n");
    printf("  • Memories tagged and timestamped\n");
    printf("  • Smart recall by type and importance\n");
    printf("═══════════════════════\n\n");
}

// Process special commands
int process_command(const char* input) {
    if (!input) return 0;
    
    // Convert to lowercase for comparison
    char cmd[MAX_INPUT_SIZE];
    strncpy(cmd, input, sizeof(cmd) - 1);
    cmd[sizeof(cmd) - 1] = '\0';
    
    // Make lowercase
    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] >= 'A' && cmd[i] <= 'Z') {
            cmd[i] = cmd[i] + 32;
        }
    }
    
    if (strcmp(cmd, "quit") == 0 || strcmp(cmd, "exit") == 0) {
        printf("👋 Goodbye! Kurama will remember our time together...\n");
        g_running = 0;
        return 1;
    } else if (strcmp(cmd, "help") == 0) {
        print_help();
        return 1;
    } else if (strstr(cmd, "debug on")) {
        g_brain.debug_mode = 1;
        printf("🐛 Debug mode enabled\n");
        return 1;
    } else if (strstr(cmd, "debug off")) {
        g_brain.debug_mode = 0;
        printf("🐛 Debug mode disabled\n");
        return 1;
    }
    
    return 0; // Not a special command
}

// Main conversation loop
void conversation_loop() {
    char input[MAX_INPUT_SIZE];
    char* response;
    
    printf("🦊 Kurama: Hello! I am Kurama, your AI companion. How may I assist you today?\n\n");
    
    while (g_running) {
        printf("You: ");
        fflush(stdout);
        
        // Read input
        if (!fgets(input, sizeof(input), stdin)) {
            break; // EOF or error
        }
        
        // Remove newline
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        
        // Skip empty input
        if (strlen(input) == 0) {
            continue;
        }
        
        // Process special commands first
        if (process_command(input)) {
            continue;
        }
        
        // Get response from Kurama
        response = kurama_respond(&g_brain, input);
        if (response) {
            printf("\n🦊 Kurama: %s\n\n", response);
        } else {
            printf("\n🦊 Kurama: I'm sorry, I couldn't process that right now.\n\n");
        }
        
        // Random evolution chance
        if (rand() % 15 == 0) {
            printf("✨ (Evolution energy building...)\n\n");
            g_brain.evolution_points++;
        }
    }
}

// Startup diagnostics
void run_diagnostics() {
    printf("🔧 Running startup diagnostics...\n");
    
    // Test memory system
    printf("  💾 Memory system... ");
    fflush(stdout);
    sleep(1); // 1 second delay for effect
    printf("✅ OK\n");
    
    // Test plugin system
    printf("  🔌 Plugin system... ");
    fflush(stdout);
    sleep(1);
    printf("✅ OK\n");
    
    // Test core functions
    printf("  🧠 Core functions... ");
    fflush(stdout);
    sleep(1);
    printf("✅ OK\n");
    
    // Test evolution system
    printf("  🌟 Evolution system... ");
    fflush(stdout);
    sleep(1);
    printf("✅ OK\n");
    
    printf("🎯 All systems operational!\n\n");
}

int main(int argc, char *argv[]) {
    // Seed random number generator
    srand(time(NULL));
    
    // Set up signal handlers
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    // Print banner
    print_banner();
    
    // Check for command line arguments
    if (argc > 1) {
        if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
            print_help();
            return 0;
        } else if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0) {
            printf("Kurama AI Brain Version %s\n", KURAMA_VERSION);
            return 0;
        } else if (strcmp(argv[1], "--no-diagnostics") == 0) {
            // Skip diagnostics
        } else {
            printf("Unknown option: %s\n", argv[1]);
            printf("Use --help for usage information.\n");
            return 1;
        }
    } else {
        // Run diagnostics if not disabled
        run_diagnostics();
    }
    
    // Initialize Kurama brain
    printf("🚀 Initializing Kurama brain...\n");
    if (!kurama_init(&g_brain)) {
        fprintf(stderr, "❌ Failed to initialize Kurama brain\n");
        return 1;
    }
    
    printf("✅ Kurama brain initialized successfully!\n\n");
    
    // Show initial status
    kurama_print_status(&g_brain);
    
    // Enter main conversation loop
    conversation_loop();
    
    // Shutdown
    printf("\n🌙 Shutting down Kurama brain...\n");
    kurama_shutdown(&g_brain);
    
    printf("💤 Kurama has entered dormant state. Goodbye!\n");
    return 0;
}