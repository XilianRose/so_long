# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mstegema <mstegema@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/10 14:19:38 by mstegema      #+#    #+#                  #
#    Updated: 2023/07/05 16:45:28 by mstegema      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= so_long

# compilation
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
HEADER	= $(INCDIR)/so_long.h
LIBFT	= libft/bin/libft.a
MLX42	= MLX42/build/libmlx42.a
ifdef AT_HOME
LINKS	= -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"
else
LINKS	= -lglfw3 -framework Cocoa -framework OpenGL -framework IOkit
endif

# directories
SRCDIR	= src
INCDIR	= inc
OBJDIR	= obj
BINDIR	= bin

# sources
SRCS	= src/so_long.c \
		src/map_validation.c \
		src/window_management.c \
		src/load_assets.c \
		src/rendering.c \
		src/gameplay.c \
		src/utils.c
OBJS	= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# colours
PURPLE	= \033[0;35m
NC		= \033[0m

all: $(LIBFT) $(MLX42) $(BINDIR)/$(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft

$(MLX42):
	@cmake -B MLX42/build ./MLX42
	@cmake --build MLX42/build -j4

$(BINDIR)/$(NAME): $(OBJS)
	@mkdir -p $(BINDIR)
	@$(CC) -o $(BINDIR)/$(NAME) $(OBJS) $(LIBFT) $(MLX42) $(LINKS)
	@echo "$(PURPLE)$(NAME)$(NC) has been created"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	@mkdir -p $(OBJDIR)
	@$(CC) -c $(CFLAGS) $< -o $@
	@echo "Compiling: $(PURPLE)$<$(NC)"

home:
	$(MAKE) AT_HOME=1

clean:
	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJDIR)
	@echo "$(PURPLE)object files$(NC) have been removed"

fclean: clean
	@$(MAKE) fclean -C ./libft
	@rm -rf MLX42/build
	@rm -rf $(BINDIR)
	@echo "$(PURPLE)$(NAME) & directories$(NC) have been removed"

re: fclean all

.PHONY: all clean fclean re
