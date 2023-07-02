# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mstegema <mstegema@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/10 14:19:38 by mstegema      #+#    #+#                  #
#    Updated: 2023/07/02 12:54:25 by mstegema      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -lglfw3 -framework Cocoa -framework OpenGL -framework IOkit

gcc -lglfw3 -framework Cocoa -framework OpenGL -framework IOkit MLX42/build/libmlx42.a
gcc -lglfw3 -framework Cocoa -framework OpenGL -framework IOkit -g MLX42/build/libmlx42.a libft/bin/libft.a
gcc -lglfw3 -framework Cocoa -framework OpenGL -framework IOkit -g inc/MLX42/build/libmlx42.a inc/libft/bin/libft.a src/*.c
gcc -Wall -Wextra -Werror -g -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/" inc/MLX42/build/libmlx42.a inc/libft/bin/libft.a src/*.c
NAME = so_long.a

# directories
SRCDIR = src
INCDIR = inc
OBJDIR = obj
BINDIR = bin

SRCS = src/
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
CFLAGS = -Wall -Wextra -Werror
HEADER = $(INCDIR)/libft.h
PURPLE = \033[0;35m
NC = \033[0m

all: $(BINDIR)/$(NAME)

$(BINDIR)/$(NAME): $(OBJS)
	@mkdir -p $(BINDIR)
	@ar -rcs $(BINDIR)/$(NAME) $(OBJS)
	@echo "$(PURPLE)$(NAME)$(NC) has been created"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	@mkdir -p $(OBJDIR)
	@cc -c $(CFLAGS) $< -o $@
	@echo "Compiling: $(PURPLE)$<$(NC)"

clean:
	@rm -f $(OBJDIR)/*.o
	@echo "$(PURPLE)object files$(NC) have been removed"

fclean: clean
	@rm -f $(BINDIR)/$(NAME)
	@rmdir $(BINDIR)
	@rmdir $(OBJDIR)
	@echo "$(PURPLE)$(NAME) & directories$(NC) have been removed"

re: fclean all

.PHONY: all clean fclean re
