#Variablen die gebraucht werden
CC		= g++
CCFLAGS	= -Wall -g
LDFLAGS	= -g -lncurses
OBJ = card_deck.o server.o poker_player.o poker_game.o socket.o
NAME = server
dependfile = .depend
SRC		= $(OBJ:%o=%cpp) $(OBJ:%o=%hpp)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -c $<

dep: $(SRC)
	$(CC) -MM $(SRC) > $(DEPENDFILE)

-include $(DEPENDFILE)


.PHONY:
ctags:
	ctags -R .
	
.PHONY:
clean:
	rm $(OBJ) $(NAME) 2>/dev/null

.PHONY:
veryclean:
	rm $(OBJ) $(NAME) tags 2>/dev/null
	rm tags 2>/dev/null

#.PHONY:
run: server
	clear
	./server
