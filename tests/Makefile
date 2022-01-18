NAME = ../src/NullPacketComms/NullPacketComms

LIBS = -lgtest_main -lgtest -lpthread

ClassTests = ./modules/ClassTests
ReadPacketTests = ./modules/ReadPacketTests
WritePacketTests = ./modules/WritePacketTests

debug: all

run-debug:
	./${NAME}

all: $(NAME).o $(ClassTests).o $(ReadPacketTests).o $(WritePacketTests).o Arduino.o
	c++ -lstdc++ $(LIBS) -o $(NAME) $(ClassTests).o $(ReadPacketTests).o $(WritePacketTests).o $(NAME).o Arduino.o

compile: $(NAME).o

clean:
	find . -name '*.o' -exec rm -f {} ';'
	find . -name $(NAME) -exec rm -f {} ';'

.cpp.o:
	g++ -I. -c -o $@ $<
