NAME 	= 	zappy

CC		= 	gcc

INCS 	= 	./incs

SERVER 	= 	./server
INIT 	= 	$(SERVER)/init
NW 		= 	$(SERVER)/network
STRUCT 	= 	$(SERVER)/struct
UTILS 	= 	$(SERVER)/utils
IA 		= 	$(SERVER)/clientIA
GUI		= 	$(SERVER)/clientGUI
EGG 	= 	$(SERVER)/egg
SPAWN	=	$(SERVER)/foodSpawn

COMMUNICATION = $(SERVER)/communications

SRC 	+= 	main.c \

SRC		+=	$(SPAWN)/foodSpawn.c

SRC 	+= 	$(SERVER)/schedule.c \
			$(SERVER)/release.c \
			$(SERVER)/signals.c \
			$(SERVER)/find_func_ia.c \
			$(SERVER)/find_func_gui.c \
			$(SERVER)/team.c \
			$(SERVER)/display_info.c \
			$(SERVER)/display2.c	\

SRC 	+=  $(IA)/alloc_client_ia.c \
			$(IA)/move.c \
			$(IA)/right.c \
			$(IA)/left.c \
			$(IA)/see.c \
			$(IA)/take_obj.c \
			$(IA)/put_obj.c \
			$(IA)/expulse.c \
			$(IA)/broadcast.c \
			$(IA)/incantation.c \
			$(IA)/fork.c \
			$(IA)/connect_nbr.c \
			$(IA)/case.c		\
			$(IA)/inventory.c	\
			$(IA)/map.c	\
			$(IA)/init_incantation_checks.c	\
			$(IA)/broadcast_utils.c	\
			$(IA)/inventory_utils.c	\
			$(IA)/decrement_food.c	\
			$(IA)/vectors.c	\
			$(IA)/incantation_utils.c \
			$(IA)/expulse_utils.c \
			$(IA)/see_utils.c \
			$(IA)/see_utils2.c \
			$(IA)/see_utils3.c \
			$(IA)/see_utils4.c \
			$(IA)/map_utils.c	\

SRC   += $(COMMUNICATION)/serv_to_gui.c
SRC   += $(COMMUNICATION)/serv_to_gui_2.c
SRC   += $(COMMUNICATION)/serv_to_gui_3.c
SRC   += $(COMMUNICATION)/serv_to_gui_4.c
SRC   += $(COMMUNICATION)/serv_to_gui_5.c
SRC   += $(COMMUNICATION)/serv_to_gui_6.c

SRC 	+=  $(GUI)/alloc_client_gui.c \
			$(GUI)/get_client_ia.c \
			$(GUI)/msz.c \
			$(GUI)/bct.c \
			$(GUI)/mct.c \
			$(GUI)/tna.c \
			$(GUI)/ppo.c \
			$(GUI)/plv.c \
			$(GUI)/pin.c \
			$(GUI)/sgt.c \
			$(GUI)/sst.c \

SRC		+=	$(INIT)/init_server.c \
			$(INIT)/fill_option.c \
			$(INIT)/func_parse.c \
			$(INIT)/func_parse2.c \

SRC 	+= 	$(STRUCT)/list.c \
			$(STRUCT)/circular_buffer.c \
			$(STRUCT)/utils_buffer.c \
			$(STRUCT)/release_node.c \
			$(STRUCT)/iter_list.c \

SRC 	+= 	$(UTILS)/is_digit.c \
			$(UTILS)/free_va_arg.c \
			$(UTILS)/display_info.c \
			$(UTILS)/time.c \
			$(UTILS)/concatList.c \
			$(UTILS)/parse_arg_int.c \

SRC 	+= 	$(NW)/create_socket_tcp.c \
			$(NW)/connexion.c \
			$(NW)/monitor_socket.c \
			$(NW)/routine_connexion.c \
			$(NW)/routine_clients_ia.c \
			$(NW)/routine_clients_gui.c \
			$(NW)/choose_graphic_or_ia.c \
			$(NW)/action_network.c \
			$(NW)/choose_client.c \
			$(NW)/write_ia.c \
			$(NW)/write_gui.c \

SRC 	+=  $(EGG)/alloc_egg.c \
			$(EGG)/is_in_list_egg.c \
			$(EGG)/routine_egg.c \

OBJ 	= 	$(SRC:.c=.o)

CFLAGS 	= 	-W -Wall -Wextra -I$(INCS)
LDFLAGS = 	-lm

RM 		= 	rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
