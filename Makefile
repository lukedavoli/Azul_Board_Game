.default: all

all: azul

clean:
	rm -f azul *.o

azul: BrokenRow.o Factory.o FactoryZero.o GameEngine.o LinkedList.o Menu.o Mosaic.o Player.o StorageRow.o main.o
	g++ -Wall -Werror -std=c++14 -g -O0 -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O0 -c $^
