#Variablen die gebraucht werden
CXX		= g++-4.7
CFLAGS	= -Wall -g -std=c++11
LDFLAGS	= -g -lncursesw
OBJ = card_deck.o server.o poker_player.o poker_game.o socket.o FiveEval.o SevenEval.o
NAME = server
dependfile = .depend
SRC		= $(OBJ:%o=%cpp) $(OBJ:%o=%hpp)

$(NAME): $(OBJ)
	$(CXX) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

server.o: server.cpp
	$(CXX) $(CFLAGS) -c $<

%.o: %.cpp %.hpp
	$(CXX) $(CFLAGS) -c $<

dep: $(SRC)
	$(CXX) -MM $(SRC) > $(DEPENDFILE)

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

client: server
	nc localhost 8888
