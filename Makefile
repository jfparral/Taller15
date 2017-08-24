all: deamon
taller15 : deamon.c
	gcc -Wall -g deamon.c -o taller15

clear:
	rm -rf taller15