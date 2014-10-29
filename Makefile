all: build run

build:
	g++ main.cpp Hangman.cpp -o hello

run:
	./hello

clean:
	rm -f *.o hello