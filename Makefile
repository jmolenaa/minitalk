NAME = name
CLIENT = client
SERVER = server
SRC_CLIENT = client.c ft_minitalk_utils.c sending_functions.c
SRC_SERVER = server.c ft_minitalk_utils.c receiving_functions.c
CFLAGS = -Wall -Werror -Wextra
CC = cc
OBJ_DIR = obj
LIBFT = libft/libft.a
LIBFT_DIR = libft
LIGHTGREEN=\033[1;32m
EXIT=\033[0m
DIM=\033[2m
YELLOW=\033[1;33m
OBJ_DIR = obj
SRC_DIR = src
OBJ_CLIENT = $(SRC_CLIENT:%.c=$(OBJ_DIR)/%.o)
OBJ_SERVER = $(SRC_SERVER:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT_DIR) $(CLIENT) $(SERVER)

$(CLIENT): $(OBJ_CLIENT) | $(LIBFT)
	@echo "\n $(LIGHTGREEN)|C|o|m|p|i|l|i|n|g|  |C|l|i|e|n|t|$(EXIT)\n";
	@$(CC) $(CFLAGS) -o client -iquote includes -iquote libft/includes $(OBJ_CLIENT) $(LIBFT)

$(SERVER): $(OBJ_SERVER) | $(LIBFT)
	@echo "\n $(LIGHTGREEN)|C|o|m|p|i|l|i|n|g|  |S|e|r|v|e|r|$(EXIT)\n";
	@$(CC) $(CFLAGS) -o server -iquote includes -iquote libft/includes $(OBJ_SERVER) $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) -iquote includes -iquote libft/includes -c $(CFLAGS) -o $@ $<

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(LIBFT_DIR): 
	@git clone https://github.com/jmolenaa/Codam_libft.git $(LIBFT_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf obj
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	@echo "\n $(YELLOW) |D|e|l|e|t|i|n|g|  |E|x|e|c|u|t|a|b|l|e|s|$(EXIT)\n";
	@rm -rf obj
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(CLIENT) $(SERVER)

re: fclean
	@$(MAKE) all

binaries: $(NAME)

.PHONY: all fclean clean re $(LIBFT)
