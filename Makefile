NAME = pendulum
CC = gcc

INC_DIR = inc
SRC_DIR = src
UTIL_DIR = $(SRC_DIR)/util
BUILD_DIR = build

CFLAGS = -Wall -Wextra -I $(INC_DIR) `pkg-config --cflags --libs sdl3` -lm

SRC = $(wildcard $(SRC_DIR)/*.c $(UTIL_DIR)/*.c)
OBJ = $(addprefix $(BUILD_DIR)/, $(notdir $(SRC:.c=.o)))


all: $(NAME)
	./$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/%.o: $(UTIL_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	echo $(OBJ)
	rm -rf $(BUILD_DIR) $(NAME)

.PHONY: all clean

