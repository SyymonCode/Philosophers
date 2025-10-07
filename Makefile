NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -I.  # -I. to include philolib.h from root

SRC_DIR = ./srcs
OBJ_DIR = ./obj

SRC = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/helpers.c \
	$(SRC_DIR)/routine.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/death.c \
	$(SRC_DIR)/forks.c

OBJ = \
	$(OBJ_DIR)/main.o \
	$(OBJ_DIR)/helpers.o \
	$(OBJ_DIR)/routine.o \
	$(OBJ_DIR)/init.o \
	$(OBJ_DIR)/death.o \
	$(OBJ_DIR)/forks.o

all: $(NAME)

$(NAME): $(OBJ) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
