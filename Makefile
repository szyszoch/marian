NAME := marian
SRCS := $(wildcard src/*.c src/**/*.c src/**/**/*.c) 
OBJS := $(SRCS:src/%.c=obj/%.o) obj/glad.o

CC := gcc
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS := -I ./src -I ./lib -I ./lib/glfw/include
LDFLAGS := -Llib/glfw/build/src
LDLIBS := -lglfw3 -lgdi32

all: dirs libs $(NAME)

dirs:
	@if not exist obj mkdir obj
	@if not exist bin mkdir bin

libs:
	$(info Compiling glad library)
	@$(CC) -o obj/glad.o -c lib/glad/glad.c -Ilib/glad
	$(info Compiling glfw library)
	@cd lib/glfw && \
		cmake -S . -B build -D GLFW_BUILD_DOCS=off -D GLFW_BUILD_EXAMPLES=off \
		-D GLFW_BUILD_TESTS=off -G "Unix Makefiles" && \
		cd build && \
		make --silent

$(NAME): $(OBJS)
	$(info Compiling program)
	@$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o bin/$(NAME)
	$(info Compiling completed)

obj/%.o: src/%.c
	@if not exist $(subst /,\\,$(@D)) mkdir $(subst /,\\,$(@D))
	$(info Compiling $<)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	@if exist obj rmdir /s /q obj
	@if exist bin rmdir /s /q bin