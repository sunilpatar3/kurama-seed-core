# Kurama AI Brain Makefile
# Compiles all modules into kurama_brain executable

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -DNDEBUG -s

# Directories
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = .

# Target executable
TARGET = kurama_brain

# Source files
SOURCES = kurama_brain.c kurama_core.c kurama_memory.c kurama_plugin.c
HEADERS = kurama_core.h kurama_memory.h kurama_plugin.h

# Object files (in obj directory)
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

# Default target
all: $(TARGET)

# Create directories if they don't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Build the main executable
$(TARGET): $(OBJ_DIR) $(OBJECTS)
	@echo "🔗 Linking $(TARGET)..."
	$(CC) $(CFLAGS) $(OBJECTS) -o $(BIN_DIR)/$(TARGET)
	@echo "✅ Build complete: $(TARGET)"
	@echo "🚀 Run with: ./$(TARGET)"

# Compile individual object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "🔧 Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)
	@echo "🐛 Debug build complete"

# Release build
release: CFLAGS += $(RELEASE_FLAGS)
release: clean $(TARGET)
	@echo "🚀 Release build complete"

# Clean build artifacts
clean:
	@echo "🧹 Cleaning build artifacts..."
	@rm -rf $(OBJ_DIR)
	@rm -f $(TARGET)
	@echo "✨ Clean complete"

# Install (copy to /usr/local/bin)
install: $(TARGET)
	@echo "📦 Installing $(TARGET) to /usr/local/bin..."
	@sudo cp $(TARGET) /usr/local/bin/
	@sudo chmod +x /usr/local/bin/$(TARGET)
	@echo "✅ Installation complete"

# Uninstall
uninstall:
	@echo "🗑️ Uninstalling $(TARGET)..."
	@sudo rm -f /usr/local/bin/$(TARGET)
	@echo "✅ Uninstallation complete"

# Run the program
run: $(TARGET)
	@echo "🚀 Running $(TARGET)..."
	@./$(TARGET)

# Run with debug output
run-debug: debug
	@echo "🐛 Running $(TARGET) in debug mode..."
	@./$(TARGET)

# Check for memory leaks (requires valgrind)
memcheck: debug
	@echo "🔍 Running memory check..."
	@valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Code analysis (requires cppcheck)
check:
	@echo "🔍 Running static analysis..."
	@cppcheck --enable=all --std=c99 $(SOURCES)

# Format code (requires clang-format)
format:
	@echo "🎨 Formatting code..."
	@clang-format -i $(SOURCES) $(HEADERS)

# Generate documentation (requires doxygen)
docs:
	@echo "📚 Generating documentation..."
	@doxygen Doxyfile

# Show project info
info:
	@echo "╔══════════════════════════════════════════════════════════════╗"
	@echo "║                   🦊 KURAMA AI BRAIN 🦊                      ║"
	@echo "║                        Build System                          ║"
	@echo "╠══════════════════════════════════════════════════════════════╣"
	@echo "║ Compiler: $(CC)                                               ║"
	@echo "║ Flags:    $(CFLAGS)                          ║"
	@echo "║ Target:   $(TARGET)                                      ║"
	@echo "║ Sources:  $(words $(SOURCES)) files                                         ║"
	@echo "║ Headers:  $(words $(HEADERS)) files                                         ║"
	@echo "╚══════════════════════════════════════════════════════════════╝"

# Help target
help:
	@echo "╔══════════════════════════════════════════════════════════════╗"
	@echo "║                   🦊 KURAMA AI BRAIN 🦊                      ║"
	@echo "║                     Makefile Help                           ║"
	@echo "╠══════════════════════════════════════════════════════════════╣"
	@echo "║ BUILD TARGETS:                                               ║"
	@echo "║   make          - Build kurama_brain (default)              ║"
	@echo "║   make debug    - Build with debug symbols                  ║"
	@echo "║   make release  - Build optimized release version           ║"
	@echo "║   make clean    - Remove build artifacts                    ║"
	@echo "║                                                              ║"
	@echo "║ RUN TARGETS:                                                 ║"
	@echo "║   make run      - Build and run kurama_brain                ║"
	@echo "║   make run-debug- Build and run in debug mode               ║"
	@echo "║                                                              ║"
	@echo "║ INSTALL TARGETS:                                             ║"
	@echo "║   make install  - Install to /usr/local/bin                 ║"
	@echo "║   make uninstall- Remove from /usr/local/bin                ║"
	@echo "║                                                              ║"
	@echo "║ DEVELOPMENT TARGETS:                                         ║"
	@echo "║   make memcheck - Run with valgrind memory check            ║"
	@echo "║   make check    - Run static analysis with cppcheck         ║"
	@echo "║   make format   - Format code with clang-format             ║"
	@echo "║   make docs     - Generate documentation                    ║"
	@echo "║                                                              ║"
	@echo "║ INFO TARGETS:                                                ║"
	@echo "║   make info     - Show project information                  ║"
	@echo "║   make help     - Show this help                            ║"
	@echo "╚══════════════════════════════════════════════════════════════╝"

# Dependencies
$(OBJ_DIR)/kurama_brain.o: kurama_core.h
$(OBJ_DIR)/kurama_core.o: kurama_core.h kurama_memory.h kurama_plugin.h
$(OBJ_DIR)/kurama_memory.o: kurama_memory.h
$(OBJ_DIR)/kurama_plugin.o: kurama_plugin.h

# Phony targets
.PHONY: all debug release clean install uninstall run run-debug memcheck check format docs info help