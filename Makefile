COMPILER = gcc

COMPILER_FLAGS = -std=c11
COMPILER_FLAGS += -O3
COMPILER_FLAGS += -Wall -Wextra -Wstrict-aliasing -Wno-int-conversion
COMPILER_FLAGS += -Ilib/glad/ -Ilib/glfw/include -Isrc -Ilib/cglm/include

LINKER_FLAGS = lib/glfw/src/libglfw3.a lib/cglm/libcglm.a

ifeq ($(OS), Windows_NT)
    PROGRAM = marian.exe
	LINKER_FLAGS += -lgdi32 -mwindows
	SUPPRESS_COMMAND_OUTPUT = > NUL 2>&1
	CLEAN_COMMAND = rmdir /s /q
else
    PROGRAM = marian
	LINKER_FLAGS += -lm
	SUPPRESS_COMMAND_OUTPUT = > /dev/null 2>&1
	CLEAN_COMMAND = rm -rf
endif

all: dirs libs marian

dirs:
	@echo Creating directories
ifeq ($(OS), Windows_NT)
	@if not exist "bin" mkdir bin
	@if not exist "objects" mkdir objects
else
	@mkdir -p bin
	@mkdir -p objects
endif

libs:
ifeq ($(wildcard lib/glfw/src/libglfw3.a),)
	@echo Compiling glfw3
	@cd lib/glfw && cmake . -G "Unix Makefiles" $(SUPPRESS_COMMAND_OUTPUT) && make $(SUPPRESS_COMMAND_OUTPUT)
endif
	@echo Compiling glad
	@$(COMPILER) -o objects/glad.o -Ilib/glad/glad -c lib/glad/glad/glad.c
ifeq ($(wildcard lib/cglm/libcglm.a),)	
	@echo Compiling cglm
	@cd lib/cglm && cmake . -DCGLM_STATIC=ON -G "Unix Makefiles" $(SUPPRESS_COMMAND_OUTPUT) && make $(SUPPRESS_COMMAND_OUTPUT)
endif

SOURCE = $(wildcard src/*.c)
OBJECTS = $(patsubst src/%.c, objects/%.o, $(SOURCE))
LIB_OBJECTS = objects/glad.o

marian: $(OBJECTS)
	@echo Compiling program
	@$(COMPILER) -o bin/$(PROGRAM) $^ $(LIB_OBJECTS) $(LINKER_FLAGS)

objects/%.o: src/%.c
	@echo Compiling $<
	@$(COMPILER) -o $@ -c $< $(COMPILER_FLAGS)

clean:
	@echo Deleting directories
	@$(CLEAN_COMMAND) bin 
	@$(CLEAN_COMMAND) objects