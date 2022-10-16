# FLAGS = -std=c11 -pedantic -Wall -Werror

# all: child run

run: main.c
	gcc $(FLAGS) main.c -pthread -o run

clean:
	rm -f *.out *.o run
	rm -f *.out run child *.o
