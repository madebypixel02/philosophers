# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/29 10:50:06 by aperez-b          #+#    #+#              #
#    Updated: 2023/04/08 15:04:52 by aperez-b         ###   ########.fr        #
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

SHELL=/bin/bash
UNAME = $(shell uname -s)

# Properties for MacOS
CDEBUG = #-g3 -fsanitize=address
CHECKER = tests/checker_Mac
ifeq ($(UNAME), Linux)
	#Properties for Linux
	LEAKS = valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes -s -q 
endif

# Make variables
PRINTF = printf
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror -MD
RM = rm -f
CC = gcc -pthread
SRC_DIR = src
SRC_LFT_DIR = src_lft
OBJ_DIR = obj
OBJ_LFT_DIR = obj_lft
BIN_DIR = bin
BIN = philo
NAME = $(BIN_DIR)/$(BIN)

SRC_LFT = lists.c strings.c numbers.c 
SRC = main.c philo_utils.c philo.c philo_time.c
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_LFT = $(addprefix $(OBJ_LFT_DIR)/, $(SRC_LFT:.c=.o))

# Progress vars
SRC_COUNT_TOT := $(shell expr $(shell echo -n $(SRC) | wc -w) - $(shell ls -l $(OBJ_DIR) 2>&1 | grep ".o" | wc -l) + 1)
ifeq ($(shell test $(SRC_COUNT_TOT) -le 0; echo $$?),0)
	SRC_COUNT_TOT := 1
endif
SRC_COUNT := 0
SRC_PCT = $(shell expr 100 \* $(SRC_COUNT) / $(SRC_COUNT_TOT))
SRC_LFT_COUNT_TOT := $(shell expr $(shell echo -n $(SRC_LFT) | wc -w) - $(shell ls -l $(OBJ_LFT_DIR) 2>&1 | grep ".o" | wc -l) + 1)
ifeq ($(shell test $(SRC_LFT_COUNT_TOT) -le 0; echo $$?),0)
	SRC_LFT_COUNT_TOT := 1
endif
SRC_LFT_COUNT := 0
SRC_LFT_PCT = $(shell expr 100 \* $(SRC_LFT_COUNT) / $(SRC_LFT_COUNT_TOT))

all: $(NAME)

$(NAME): $(OBJ_LFT) $(OBJ) | $(BIN_DIR)
	@$(CC) $(CFLAGS) $(CDEBUG) $(OBJ) $(OBJ_LFT) -o $@
	@$(PRINTF) "\r%100s\r$(GREEN)$(BIN) is up to date!$(DEFAULT)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(eval SRC_COUNT = $(shell expr $(SRC_COUNT) + 1))
	@$(PRINTF) "\r%100s\r[ %d/%d (%d%%) ] Compiling $(BLUE)$<$(DEFAULT)..." "" $(SRC_COUNT) $(SRC_COUNT_TOT) $(SRC_PCT)
	@$(CC) $(CFLAGS) $(CDEBUG) -c $< -o $@

$(OBJ_LFT_DIR)/%.o: $(SRC_LFT_DIR)/%.c | $(OBJ_LFT_DIR)
	@$(eval SRC_LFT_COUNT = $(shell expr $(SRC_LFT_COUNT) + 1))
	@$(PRINTF) "\r%100s\r[ %d/%d (%d%%) ] Compiling $(YELLOW)$<$(DEFAULT)..." "" $(SRC_LFT_COUNT) $(SRC_LFT_COUNT_TOT) $(SRC_LFT_PCT)
	@$(CC) $(CFLAGS) $(CDEBUG) -c $< -o $@

test: all
	@$(PRINTF) "$(YELLOW)Performing test with custom parameters...$(DEFAULT)\n\n"
	@$(PRINTF) "Command: $(GRAY)$(LEAKS)./$(NAME) $(N)$(DEFAULT)\n\n"
	@$(LEAKS)./$(NAME) $(N)

clean:
	@$(PRINTF) "$(CYAN)Cleaning up object files in $(OBJ_DIR) and $(OBJ_LFT_DIR)...$(DEFAULT)\n"
	@$(RM) -r $(OBJ_DIR)
	@$(RM) -r $(OBJ_LFT_DIR)

fclean: clean
	@$(RM) -r $(BIN_DIR)
	@$(PRINTF) "$(CYAN)Removed $(BIN)$(DEFAULT)\n"

norminette:
	@$(PRINTF) "$(CYAN)\nChecking norm for $(BIN)...$(DEFAULT)\n"
	@norminette -R CheckForbiddenSourceHeader $(SRC_DIR) $(SRC_LFT_DIR) inc/

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_LFT_DIR):
	@mkdir -p $(OBJ_LFT_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

re: fclean
	@make all

git:
	git add .
	git commit
	git push

-include $(OBJ_DIR)/*.d
-include $(OBJB_LFT_DIR)/*.d

.PHONY: all clean fclean norminette test git re
