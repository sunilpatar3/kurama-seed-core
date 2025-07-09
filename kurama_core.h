#ifndef KURAMA_CORE_H
#define KURAMA_CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024
#define MAX_RESPONSE_SIZE 2048
#define MAX_THOUGHT_SIZE 512
#define KURAMA_VERSION "1.0"

// Evolution phases enum
typedef enum {
    PHASE_DORMANT = 0,
    PHASE_AWAKENING,
    PHASE_LEARNING,
    PHASE_ADAPTING,
    PHASE_EVOLVING,
    PHASE_TRANSCENDING,
    PHASE_ENLIGHTENED,
    MAX_PHASES = 22
} EvolutionPhase;

// Kurama brain state structure
typedef struct {
    EvolutionPhase current_phase;
    int evolution_points;
    int interaction_count;
    int memory_count;
    char last_input[MAX_INPUT_SIZE];
    char last_thought[MAX_THOUGHT_SIZE];
    int is_initialized;
    int debug_mode;
} KuramaBrain;

// Core function declarations
int kurama_init(KuramaBrain *brain);
void kurama_shutdown(KuramaBrain *brain);
char* kurama_think(KuramaBrain *brain, const char* input);
char* kurama_respond(KuramaBrain *brain, const char* input);
void kurama_evolve(KuramaBrain *brain);
void kurama_print_status(const KuramaBrain *brain);
const char* kurama_get_phase_name(EvolutionPhase phase);
void kurama_debug_log(const KuramaBrain *brain, const char* message);

#endif // KURAMA_CORE_H