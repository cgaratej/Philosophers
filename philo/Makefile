# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 10:52:15 by cgaratej          #+#    #+#              #
#    Updated: 2024/09/10 16:35:09 by cgaratej         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc -g
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -fsanitize=leak
RM = rm -f

GREEN=\033[32m
LGREEN=\033[1;92m
ORANGE=\033[33m
RED = \033[1;91m
NONE=\033[0m

BUILD_DIR = build

SRC = main.c utils.c init.c
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)
DEPS = $(SRC:%.c=$(BUILD_DIR)/%.d)

all: $(NAME)

$(NAME): $(OBJ) Makefile
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "\n$(LGREEN)Create $(NAME) ✔$(NONE)\n"

$(BUILD_DIR)/%.o: %.c Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -MMD -o $@
	@echo "$(GREEN)File $< compiled ✔$(NONE)"

-include $(DEPS)

clean:
	@$(RM) -r $(BUILD_DIR)
	@echo "$(RED)Deleted .o files and .d files$(NONE)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) Deleted$(NONE)"

re: fclean all

.PHONY: all clean fclean re