# Variables
CC		:= cc
RM		:= rm -f
#CFLAGS	:= -Wall -Wextra -Werror -pthread -fsanitize=thread -g
CFLAGS	:= -Wall -Wextra -Werror -pthread -g
DEBUG	:= $(CFLAGS) -g

# Names
NAME	:= philo

# Folders
INCLUDE_DIR := include
BUILD_DIR	:= build
SRC_DIR		:= src

# Includes & Links
INCLUDE	:= -I$(INCLUDE_DIR)

# Colors
DEF_COLOR	:= \033[0;39m
GRAY		:= \033[0;90m
RED			:= \033[0;91m
GREEN		:= \033[0;92m
YELLOW		:= \033[0;93m
BLUE		:= \033[0;94m
MAGENTA		:= \033[0;95m
CYAN		:= \033[0;96m
WHITE		:= \033[0;97m

# Files
SRCS	:= $(shell find $(SRC_DIR) -name "*.c" -type f)
OBJS	:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Rules
all: $(NAME)

debug: fclean $(OBJS)
	@$(CC) $(DEBUG) $(OBJS) -o $(NAME)
	@printf "$(GREEN)$@ compiled! $(DEF_COLOR)\n"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $(NAME)
	@printf "$(GREEN)$@ compiled! $(DEF_COLOR)\n"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)Compiling: $< $(DEF_COLOR)\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	
clean:
	@rm -rf $(BUILD_DIR)
	@printf "$(GREEN)$(NAME) object files cleaned!$(DEF_COLOR)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(GREEN)$(NAME) binaries cleaned!$(DEF_COLOR)\n"

re: fclean all
	@printf "$(GREEN)Cleaned and rebuilt!$(DEF_COLOR)\n"

# Phony
.PHONY: clean fclean bonus re all debug
