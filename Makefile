NAME := marian
BIN_DIR := bin

SRC_DIR := src
SRCS := $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/**/*.c)

OBJ_DIR := obj
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC := gcc
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS := -I ./src

all: $(NAME)

$(NAME): $(OBJS)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(info Compiling program)
	@$(CC) $(OBJS) -o $(BIN_DIR)/$(NAME)
	$(info Compiling completed)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if not exist $(subst /,\\,$(@D)) mkdir $(subst /,\\,$(@D))
	$(info Compiling $<)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@if exist $(BIN_DIR) rmdir /s /q $(BIN_DIR)