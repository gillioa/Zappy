CC	=	g++ -Wall -Wextra -fstack-protector -fstack-protector-all -Wstack-protector -std=c++11 -O3

DIR_SRC =	./sources/

CXXFLAGS	+=  -I./includes
CXXFLAGS	+=  -I$(DIR_SRC)app/
CXXFLAGS	+=  -I$(DIR_SRC)login/
CXXFLAGS	+=  -I$(DIR_SRC)texture_manager/
CXXFLAGS	+=  -I$(DIR_SRC)view/
CXXFLAGS	+=  -I$(DIR_SRC)sfmltools/
CXXFLAGS	+=  -I$(DIR_SRC)collision/
CXXFLAGS	+=  -I$(DIR_SRC)color/
CXXFLAGS	+=  -I$(DIR_SRC)panel_team/
CXXFLAGS	+=  -I$(DIR_SRC)panel_time/
CXXFLAGS	+=  -I$(DIR_SRC)settings/
CXXFLAGS	+=  -I$(DIR_SRC)zappy/
CXXFLAGS	+=  -I$(DIR_SRC)zappy/map/
CXXFLAGS	+=  -I$(DIR_SRC)zappy/map/case/
CXXFLAGS	+=  -I$(DIR_SRC)zappy/player/
CXXFLAGS	+=  -I$(DIR_SRC)zappy/team/
CXXFLAGS	+=  -I$(DIR_SRC)zappy/egg/

LDFLAGS =	-L /usr/local/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lpthread -lsfml-audio

RM	=	rm -f

NAME	=	zappy_gui

SRCS	=	$(DIR_SRC)main.cpp			  	\
		$(DIR_SRC)app/App.cpp			  	\
		$(DIR_SRC)login/Login.cpp			\
		$(DIR_SRC)settings/Settings.cpp			\
		$(DIR_SRC)texture_manager/TextureManager.cpp	\
		$(DIR_SRC)view/View.cpp			  	\
		$(DIR_SRC)view/ViewFPTR.cpp			  	\
		$(DIR_SRC)view/ViewFPTRCase.cpp			  	\
		$(DIR_SRC)zappy/Zappy.cpp			\
		$(DIR_SRC)collision/CollisionEngine.cpp		\
		$(DIR_SRC)color/Color.cpp		\
		$(DIR_SRC)zappy/map/Map.cpp			\
		$(DIR_SRC)zappy/map/case/Case.cpp		\
		$(DIR_SRC)zappy/player/Player.cpp		\
		$(DIR_SRC)sfmltools/SFMLMouseEvent.cpp		\
		$(DIR_SRC)reception/Reception.cpp		\
		$(DIR_SRC)reception/FileDescr.cpp		\
		$(DIR_SRC)reception/Socket.cpp			\
		$(DIR_SRC)reception/CircularBuffer.cpp		\
		$(DIR_SRC)reception/Treatment.cpp		\
		$(DIR_SRC)zappy/team/Team.cpp 			\
		$(DIR_SRC)zappy/egg/Egg.cpp			\
		$(DIR_SRC)panel_team/PanelTeam.cpp			\
		$(DIR_SRC)panel_time/PanelTime.cpp			\


OBJS	=	$(SRCS:.cpp=.o)

%.o:		%.cpp
		@$(CC) -c $^ -o $@ $(CXXFLAGS)
		@printf " \033[32m[Compilation]\033[39m %s\n" $<

all:		$(NAME)

$(NAME):	$(OBJS)
	@printf " \033[32m[Compilation des .o]\033[39m %s\n"
	@$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)
	@printf " \033[32m[Compilation terminée avec succès]\033[39m %s\n"

clean:
	@printf " \033[31m[Suppression des .o]\033[39m\n"
	@$(RM) $(OBJS)

fclean:		clean
	@printf " \033[31m[Suppression du binaire : %s]\033[39m\n" $(NAME)
	@$(RM) $(NAME)

re:		fclean all

test:		fclean all
		$(RM) $(OBJS)
