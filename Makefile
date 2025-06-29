NAME = philo

RED = \033[0;31m
GREEN = \033[0;32m
NC = \033[0m

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3

INC_DIR = -I include/
OBJ_DIR = objs/
SRC_DIR = src/

SRC =	$(addprefix $(SRC_DIR), main.c \
								parse.c \
								utils.c \
								init.c \
								wrappers.c \
								dinner.c \
								getters_setters.c \
								sync.c \
								write.c \
								monitor.c)

OBJS = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@printf "$(GREEN)[Compiling]$(NC) %s...$(NC)\n" "$(notdir $(<))"
	@$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -no-pie $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "$(RED)[Cleaning]$(NC)\n" "$(notdir $(<))"
	@rm -f $(NAME)

re: fclean all

valg:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY: all clean fclean valg re
