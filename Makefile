# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mstegema <mstegema@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/10 14:19:38 by mstegema      #+#    #+#                  #
#    Updated: 2023/06/28 12:28:33 by mstegema      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -lglfw3 -framework Cocoa -framework OpenGL -framework IOkit

gcc -lglfw3 -framework Cocoa -framework OpenGL -framework IOkit MLX42/build/libmlx42.a
gcc -lglfw3 -framework Cocoa -framework OpenGL -framework IOkit MLX42/build/libmlx42.a libft/bin/libft.a
