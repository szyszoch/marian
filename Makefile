COMPILER = gcc

COMPILER_FLAGS = -std=c11
COMPILER_FLAGS += -O3
COMPILER_FLAGS += -Wall -Wextra -Wstrict-aliasing -Wno-int-conversion
COMPILER_FLAGS += -Ilib -Ilib/glfw/include -Isrc

LINKER_FLAGS = lib/glfw/src/libglfw3.a

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
ifeq ($(wildcard bin),)
	@echo Creating directory bin
	@mkdir bin
endif
ifeq ($(wildcard objects),)
	@echo Creating directory objects
	@mkdir objects
endif

libs:
ifeq ($(wildcard lib/glfw/src/libglfw3.a),)
	@echo Compiling glfw3
	@cd lib/glfw && cmake -G "Unix Makefiles" $(SUPPRESS_COMMAND_OUTPUT) && make $(SUPPRESS_COMMAND_OUTPUT)
endif
	@echo Compiling glad
	@$(COMPILER) -o objects/glad.o -Ilib/glad -c lib/glad/glad.c

SOURCE = $(wildcard src/*.c)
OBJECTS  = $(addprefix objects/, $(notdir $(patsubst %.c, %.o, $(SOURCE)) ) )
LIB_OBJECTS = objects/glad.o

marian: $(OBJECTS)
	@echo Compiling program
	@$(COMPILER) -o bin/$(PROGRAM) $(OBJECTS) $(LIB_OBJECTS) $(LINKER_FLAGS)

objects/%.o: src/%.c
	@echo Compiling $<
	@$(COMPILER) -o $@ -c $< $(COMPILER_FLAGS)

clean:
	@echo Deleting directory bin
	@$(CLEAN_COMMAND) bin 
	@echo Deleting directory objects
	@$(CLEAN_COMMAND) objects