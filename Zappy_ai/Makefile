##
## Makefile for makefile in /home/ambroise/PSU_2016_zappy/Zappy_ai
## 
## Made by ambroise
## Login   <ambroise.damier@epitech.eu>
## 
## Started on  Sun Jul  2 08:05:25 2017 ambroise
## Last update Sun Jul  2 08:09:01 2017 ambroise
##

CC		=	g++

SRCS		=	main.cpp	\
			ai.cpp


NAME		=	../zappy_ai

OBJS		=	$(SRCS:.cpp=.o)

CXXFLAGS	=	-W -Wall -Wextra -Werror

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(CXXFLAGS)

clean		:
			rm -f $(OBJS)

fclean		:	clean
			rm -f $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
