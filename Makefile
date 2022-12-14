# Это комментарий, который говорит, что переменная CC указывает компилятор, используемый для сборки
CC=g++
#Это еще один комментарий. Он поясняет, что в переменной CFLAGS лежат флаги, которые передаются компилятору
CFLAGS=-g -fsanitize=address,leak -c

all: stack

stack: main.o tests.o stack.o stack.h tests.h
	$(CC) -fsanitize=address,leak main.o tests.o stack.o -o stack

main.o: main.cpp stack.h tests.h
	$(CC) $(CFLAGS) main.cpp

stack.o: stack.cpp stack.h tests.h
	$(CC) $(CFLAGS) stack.cpp

tests.o: tests.cpp stack.h tests.h
	$(CC) $(CFLAGS) tests.cpp

clean:
	rm -rf *.o stack