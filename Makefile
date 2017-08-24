all: taller15
taller15: deamon.c
	gcc -Wall -g deamon.c -o taller15

clean:
	rm -rf taller15