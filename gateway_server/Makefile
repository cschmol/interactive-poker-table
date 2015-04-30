#Variablen die gebraucht werden
CC		= g++
CCFLAGS	= -Wall -g
LDGLAGS	=
OBJ = card_deck.o server.o
NAME = server
dependfile = .depend
SRC		= $(OBJ:%o=%cpp)

$(NAME): $(OBJ)
	$(CC) $(CGLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	g++ -Wall -g -c $<

dep: $(SRC)
	$(CC) -MM $(SRC) > $(DEPENDFILE)

-include $(DEPENDFILE)


.PHONY:
ctags:
	ctags -R .
	
.PHONY:
clean:
	rm $(OBJ) $(NAME)

.PHONY:
veryclean:
	rm $(OBJ) $(NAME) tags
	rm tags

