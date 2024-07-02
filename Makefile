NAME := marian
SRCS := $(wildcard src/*.c src/**/*.c src/**/**/*.c) 
OBJS := $(SRCS:src/%.c=obj/%.o)

CC := gcc
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS := -I ./include

all: dirs $(NAME)

dirs:
ifeq ($(OS),Windows_NT)
	@if not exist obj mkdir obj
	@if not exist bin mkdir bin
else
	@mkdir -p obj bin
endif

$(NAME): $(OBJS)
	$(info Compiling program)
	@$(CC) $(OBJS) -o bin/$(NAME)
	$(info Compiling completed)

obj/%.o: src/%.c
ifeq ($(OS),Windows_NT)
	@if not exist $(subst /,\\,$(@D)) mkdir $(subst /,\\,$(@D))
else
	@mkdir -p $(@D)
endif
	$(info Compiling $<)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
ifeq ($(OS),Windows_NT)
	@if exist obj rmdir /s /q obj
	@if exist bin rmdir /s /q bin
else
	@rm -rf obj bin
endif
