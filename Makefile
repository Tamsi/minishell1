##
## Makefile for  in /home/tbesson/PSU_2016_my_sokoban/bootstrap
## 
## Made by Tamsi Besson
## Login   <tbesson@epitech.net>
## 
## Started on  Tue Dec  6 14:57:19 2016 Tamsi Besson
## Last update Fri Jan 20 16:28:13 2017 Tamsi Besson
##

SRC=   	 	main.c \
		get_next_line.c \
		my_str_to_wordtab.c \
		my_strfct.c \
		my_builtin.c

NAME	=	mysh

OBJ=            $(SRC:.c=.o)

$(NAME):        $(OBJ)
		gcc -o $(NAME) $(OBJ)


all:            $(NAME)

clean:
		rm -rf $(OBJ)

fclean:		clean
		rm -rf $(NAME)

re:		fclean all

.PHONY: all clean fclean re
