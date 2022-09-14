.default: all

all: Task1 Task2 Task3 Task4 clean

clean:
	rm -rf *.o *.dSYM

Task1: Task1.o Utils.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

Task2: Task2.o Utils.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

Task3: Task3.o Utils.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

Task4: Task4.o Utils.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^