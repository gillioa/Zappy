SERVER 		= 	make -C ./ZappyServer

GUI 		= 	make -C ./ZappyGUI

IA 			= 	make -C ./ZappyIA

all:
	$(SERVER)
	$(GUI)
	$(IA)

clean:
	$(SERVER) clean
	$(GUI) clean
	$(IA) clean

fclean: clean
	$(SERVER) fclean
	$(GUI) fclean
	$(IA) fclean

server:
	$(SERVER)

gui:
	$(GUI)

ia:
	$(IA)

re : fclean all
