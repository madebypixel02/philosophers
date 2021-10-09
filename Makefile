# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/29 10:50:06 by aperez-b          #+#    #+#              #
#    Updated: 2021/10/09 14:54:35 by aperez-b         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color Aliases
DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

UNAME = $(shell uname -s)

# Properties for MacOS
ECHO = echo
CDEBUG = #-g3 -fsanitize=address
CHECKER = tests/checker_Mac
ifeq ($(UNAME), Linux)
	#Properties for Linux
	ECHO = echo -e
	LEAKS = valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes -s -q 
endif

# Make variables
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror -MD
RM = rm -f
CC = gcc -pthread
SRC_DIR = src
SRCB_DIR = srcb
SRC_LFT_DIR = src_lft
OBJ_DIR = obj
OBJB_DIR = objb
OBJ_LFT_DIR = obj_lft
BIN_DIR = bin
BIN = philo
NAME = $(BIN_DIR)/$(BIN)

SRC_LFT = ft_putstr_fd.c ft_strlen.c ft_isspace.c	\
		  ft_atoi.c ft_isdigit.c ft_putchar_fd.c	\
		  ft_putnbr_fd.c ft_free_matrix.c

SRC = main.c philo_utils.c

SRCB = 

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

OBJ_LFT = $(addprefix $(OBJ_LFT_DIR)/, $(SRC_LFT:.c=.o))

OBJB = $(addprefix $(OBJB_DIR)/, $(SRCB:.c=.o))

all: $(NAME)

$(NAME): create_dirs $(OBJ_LFT) $(OBJ)
	@$(CC) $(CFLAGS) $(CDEBUG) $(OBJ) $(OBJ_LFT) -o $@
	@$(ECHO) "$(GREEN)$(BIN) is up to date!$(DEFAULT)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(ECHO) "Compiling $(BLUE)$<$(DEFAULT)..."
	@$(CC) $(CFLAGS) $(CDEBUG) -c $< -o $@

$(OBJ_LFT_DIR)/%.o: $(SRC_LFT_DIR)/%.c
	@$(ECHO) "Compiling $(BLUE)$<$(DEFAULT)..."
	@$(CC) $(CFLAGS) $(CDEBUG) -c $< -o $@

bonus: create_dirs $(OBJ_LFT) $(OBJB)
	@$(CC) $(CFLAGS) $(CDEBUG) $(OBJB) $(OBJ_LFT) -o $(NAME)
	@$(ECHO) "$(MAGENTA)Bonus Compilation Complete in $(BIN)!$(DEFAULT)"

$(OBJB_DIR)/%.o: $(SRCB_DIR)/%.c
	@$(ECHO) "Compiling $(BLUE)$<$(DEFAULT)..."
	@$(CC) $(CFLAGS) $(CDEBUG) -c $< -o $@

create_dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_LFT_DIR)
	@mkdir -p $(OBJB_DIR)
	@mkdir -p $(BIN_DIR)

test: all
	@$(ECHO) "$(YELLOW)Performing test with custom parameters...$(DEFAULT)\n"
	@$(ECHO) "Command: $(GRAY)$(LEAKS)./$(NAME) $(N)$(DEFAULT)\n"
	@$(LEAKS)./$(NAME) $(N)

clean:
	@$(ECHO) "$(CYAN)Cleaning up object files in $(OBJ_DIR), $(OBJB_DIR) and $(OBJ_LFT_DIR)...$(DEFAULT)"
	@$(RM) -r $(OBJ_DIR)
	@$(RM) -r $(OBJB_DIR)
	@$(RM) -r $(OBJ_LFT_DIR)

fclean: clean
	@$(RM) -r $(BIN_DIR)
	@$(ECHO) "$(CYAN)Removed $(BIN)$(DEFAULT)"

norminette:
	@$(ECHO) "$(CYAN)\nChecking norm for $(BIN)...$(DEFAULT)"
	@norminette -R CheckForbiddenSourceHeader $(SRC_DIR) $(SRCB_DIR) $(SRC_LFT_DIR) inc/

re: fclean all
	@$(ECHO) "$(YELLOW)Cleaned and Rebuilt Everything for $(BIN)!$(DEFAULT)"

git:
	git add .
	git commit
	git push

-include $(OBJ_DIR)/*.d
-include $(OBJB_DIR)/*.d
-include $(OBJB_LFT_DIR)/*.d

.PHONY: all clean fclean bonus norminette create_dirs test git re
