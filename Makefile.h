CC=gccPas vraiment l
CFLAGS=-W -Wall -WERROR -ansi -pedantic
LDFLAGS=
EXEC=hello

all: hello

hello: hello.o main.o
	$(CC) -o hello hello.o main.o $(LDFLAGS)

hello.o: hello.c
	$(CC) -o hello.o -c hello.c $(CFLAGS)

main.o: main.c hello.h
	$(CC) -o main.o -c main.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
