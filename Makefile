NAME_CL = client
NAME_SR = server
NAME = minitalk
HEADERS_DIRS = includes
HEADERS = includes/minitalk.h
CC = gcc
C_FLAGS = -Wall -Wextra -Werror
SRC_DIR = srcs
OBJ_DIR = obj
SRCS = str_utils \
		mem_utils
SRC_FILE = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRCS)))
OBJ_FILE = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRCS)))
SRC_CL = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(NAME_CL)))
OBJ_CL = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(NAME_CL)))
SRC_SR = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(NAME_SR)))
OBJ_SR = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(NAME_SR)))
all: $(NAME)

$(NAME): $(NAME_SR) $(NAME_CL)

bonus: $(NAME)

$(NAME_CL): $(OBJ_FILE) $(OBJ_CL)
	$(CC) $(C_FLAGS) $(OBJ_CL) $(OBJ_FILE) -o $(NAME_CL)

$(NAME_SR): $(OBJ_FILE) $(OBJ_SR)
	$(CC) $(C_FLAGS) $(OBJ_SR) $(OBJ_FILE) -o $(NAME_SR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) -c $(C_FLAGS) -I$(HEADERS_DIRS) $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME_CL)
	rm -f $(NAME_SR)

re: fclean all

.PHONY: all, clean, fclean, re, bonus