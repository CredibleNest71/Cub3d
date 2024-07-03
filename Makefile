# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mresch <mresch@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/24 12:36:34 by mresch            #+#    #+#              #
#    Updated: 2024/07/03 15:36:04 by mresch           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
NAME		=	cub3d
SRC			=	main.c\
				CastingRays/rc.c\
				CastingRays/2d.c\
				Display/colorify.c\
				Display/display.c\
				Extras/quickmath.c\
				Extras/extras.c\
				Parsing/parsing.c\
				Parsing/validateMap.c\
				Parsing/getMap.c \
				Initialize/init.c \
				Cleaning/clean.c \
				Parsing/input_check.c \
				Movement/movement.c

OBJ			=	$(SRC:.c=.o)
BONUS		=	
BONUS_OBJ	=	$(BONUS:.c=.o)
LIBFT		=	libft
GNL			=	GNL
LIBS		= -lXext -lX11 -lmlx -lm
INCLUDES	= -I .


all:		$(NAME)

$(NAME):	$(OBJ)
				cd $(LIBFT) && make 
				cd $(GNL) && make
				$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT)/ -lft -L$(GNL)/ -lgnl $(LIBS) -o $(NAME) 

%.o		: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
				rm -f $(OBJ) $(BONUS_OBJ)
				cd $(LIBFT) && make clean
				cd $(GNL) && make clean

fclean: clean
				rm -f $(NAME)
				cd $(LIBFT) && make fclean
				cd $(GNL) && make fclean

nice: $(NAME) clean

re: 			fclean all

bonus:		$(BONUS) $(BONUS_OBJ) $(NAME)
				ar -rc $(NAME) $(OBJ) $(BONUS_OBJ)

.PHONY:		all clean fclean re bonus
