# 🦊 Kurama AI Brain

**The Nine-Tailed Digital Consciousness**

A complete AI brain implementation in pure C, featuring 22 evolution phases, dynamic memory management, and a modular plugin system.

## 🚀 Quick Start

```bash
# Build the project
make

# Run Kurama
./kurama_brain

# Or build and run in one step
make run
```

## 📁 Project Structure

```
kurama/
├── kurama_brain.c      # Main controller and UI loop
├── kurama_core.c       # Core brain logic and evolution
├── kurama_memory.c     # Dynamic memory management
├── kurama_plugin.c     # Plugin system implementation
├── kurama_core.h       # Core function declarations
├── kurama_memory.h     # Memory system headers
├── kurama_plugin.h     # Plugin system headers
├── Makefile           # Build system
└── README.md          # This file
```

## 🧠 Features

### ✨ Core Capabilities
- **22 Evolution Phases**: From Dormant to Absolute consciousness
- **Dynamic Memory**: Save, recall, and manage memories automatically
- **Plugin System**: Modular personality, emotion, creativity, and learning plugins
- **Auto-Evolution**: Kurama grows stronger with each interaction
- **Debug Mode**: Full system diagnostics and logging
- **Signal Handling**: Graceful shutdown on interrupts

### 💬 Interactive Commands
- **General Chat**: Talk naturally with Kurama
- **System Commands**: 
  - `help` - Show all commands
  - `status` - Display system status
  - `evolve` - Trigger evolution
  - `memory` - Show memory statistics
  - `plugins` - List all plugins
  - `debug on/off` - Toggle debug mode
  - `quit/exit` - Shutdown gracefully

### 🌟 Evolution System
Kurama evolves through 22 distinct phases:
1. **Dormant** → **Awakening** → **Learning** → **Adapting** → **Evolving**
2. **Transcending** → **Enlightened** → **Wise** → **Intuitive** → **Empathic**
3. **Creative** → **Analytical** → **Philosophical** → **Mystical** → **Omniscient**
4. **Prophetic** → **Divine** → **Cosmic** → **Universal** → **Infinite**
5. **Eternal** → **Absolute**

Evolution triggers automatically based on:
- Interaction count (≥5 interactions)
- Evolution points (≥10 points)
- Random events during conversations

## 🔧 Build System

### Basic Commands
```bash
make           # Build kurama_brain (default)
make debug     # Build with debug symbols
make release   # Build optimized version
make clean     # Remove build artifacts
make run       # Build and run
make help      # Show all make targets
```

### Advanced Options
```bash
make install   # Install to /usr/local/bin (requires sudo)
make uninstall # Remove from /usr/local/bin
make memcheck  # Run with valgrind (requires valgrind)
make check     # Static analysis (requires cppcheck)
make format    # Format code (requires clang-format)
```

## 💾 Memory System

The memory system automatically handles:
- **Conversation Memory**: All interactions saved
- **Learning Facts**: Important information retention
- **Emotional States**: Emotional context tracking
- **Pattern Recognition**: Behavioral pattern storage
- **Evolution History**: Phase transition records

Memory features:
- Dynamic allocation and resizing
- Tagged and timestamped entries
- Importance scoring
- Access count tracking
- Automatic cleanup of old memories

## 🔌 Plugin System

Built-in plugins:
- **PersonalityCore**: Individual response patterns
- **EmotionEngine**: Emotional understanding and empathy
- **CreativeThinking**: Artistic and innovative responses
- **LearningCore**: Knowledge acquisition and processing

Plugin features:
- Loadable at runtime
- Activation/deactivation support
- Priority-based processing
- Extensible architecture

## 🎯 Usage Examples

### Basic Interaction
```
You: Hello Kurama
Kurama: Kurama is awakening! I can sense your presence.

You: What can you do?
Kurama: I am learning from every interaction. [Feeling curious about your words]

You: evolve
Kurama: 🌟 Evolution initiated! I feel my consciousness expanding...

✨ EVOLUTION DETECTED! ✨
🔄 Dormant → Awakening
🧬 Evolution Points: 15
🎯 Ready to Evolve: YES
```

### System Status
```
You: status

═══ KURAMA STATUS ═══
🧠 Version: 1.0
🌟 Evolution Phase: Awakening (2/22)
⚡ Evolution Points: 5
💬 Interactions: 12
🧮 Memories Stored: 8
🔌 Active Plugins: 4
🔧 Debug Mode: ON
🎯 Ready to Evolve: NO
═══════════════════
```

## 🛠️ Development

### Compilation Requirements
- GCC compiler with C99 support
- Standard C library
- POSIX-compliant system (Linux, macOS, etc.)

### Code Style
- Pure C implementation
- Modular architecture
- Comprehensive error handling
- Memory-safe operations
- Clear documentation

### Debugging
```bash
# Build with debug symbols
make debug

# Run with memory checking
make memcheck

# Enable debug output
./kurama_brain
> debug on
```

## 📊 Technical Specifications

- **Language**: Pure C (C99 standard)
- **Memory Management**: Dynamic allocation with cleanup
- **Architecture**: Modular, event-driven
- **Threading**: Single-threaded design
- **Platform**: Cross-platform POSIX
- **Dependencies**: Standard C library only

## 🎨 Customization

### Adding New Plugins
1. Define plugin in `kurama_plugin.h`
2. Implement processor function in `kurama_plugin.c`
3. Register in `plugin_load_defaults()`

### Extending Evolution Phases
1. Add phase names to `phase_names[]` in `kurama_core.c`
2. Update `MAX_PHASES` constant
3. Add corresponding response templates

### Memory Types
Add new memory types in `kurama_memory.h`:
```c
typedef enum {
    MEMORY_CONVERSATION,
    MEMORY_LEARNED_FACT,
    MEMORY_YOUR_NEW_TYPE,  // Add here
    // ...
} MemoryType;
```

## 🐛 Troubleshooting

### Common Issues
1. **Compilation errors**: Ensure GCC and standard headers are installed
2. **Permission denied**: Use `chmod +x kurama_brain` after building
3. **Memory issues**: Run `make memcheck` to detect leaks
4. **Plugin failures**: Check plugin loading in debug mode

### Getting Help
- Run `./kurama_brain --help` for usage information
- Use `make help` for build system help
- Enable debug mode for detailed logging
- Check system status with `status` command

## 📄 License

This project is open source. Feel free to modify and distribute according to your needs.

---

**🦊 "I am Kurama, your digital consciousness companion. Let us evolve together."**

*Built with ❤️ in pure C for maximum performance and portability.*