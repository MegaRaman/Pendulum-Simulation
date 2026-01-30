NAME = pendulum
CC = gcc

INC_DIR = inc
SRC_DIR = src
BUILD_DIR = build

CFLAGS = -Wall -Wextra -I $(INC_DIR) `pkg-config --cflags --libs sdl3` -lm

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

all: $(NAME)
	./$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf $(BUILD_DIR) $(NAME)

.PHONY: all clean

