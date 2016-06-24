##
## Makefile for  in /home/remaud_c/Code/TPs/my_script/MyS
##
## Made by remaud_c
## Login   <remaud_c@epitech.net>
##
## Started on  Fri Feb 14 12:01:16 2014 remaud_c
## Last update Wed Jun 11 16:48:41 2014 courtu_r
##

CC	=	g++ -W -Wall -std=c++0x

LDFLAGS +=	-lboost_system -lboost_date_time -lboost_thread -lboost_serialization -lpthread -std=c++0x -W -Wall

DIR	= 	Code/

RM	=	rm -f

NAME	=	clientIA

SRCS	=	$(DIR)Client.cpp		\
		$(DIR)ClientChecker.cpp		\
		$(DIR)IA.cpp			\
		$(DIR)Inventory.cpp		\
		$(DIR)main.cpp

OBJS	=	$(SRCS:.cpp=.o)

%.o:		%.cpp
		$(CC) -c $^ -o $@ $(CXXFLAGS)

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC)  -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

test:		fclean all
		$(RM) $(OBJS)
