NAME = NullPacketComms

LIBS = -lgtest_main -lgtest -lpthread

TEST = ./modules/NPCTestSuite


debug: all

run-debug:
	./${NAME}

all: $(NAME).o $(TEST).o Arduino.o
	c++ -lstdc++ $(LIBS) -o $(NAME) $(TEST).o $(NAME).o Arduino.o

compile: $(NAME).o

clean:
	find . -name '*.o' -exec rm -f {} ';'
	find . -name $(NAME) -exec rm -f {} ';'

.cpp.o:
	g++ -I. -c -o $@ $<
