##########################################
#         MakeFile para Server           #
#   		 Projecto LABC               #
#	João Lucas Pires e Solange Sampaio   #
#        201606617 e 201603610           #
##########################################

# "make" para compilar
# "make clean" para apagar ficheiros *.o

CC=gcc
CFLAGS=-g -Wall

all: server

server: server.o server_menus.o statistics.o usermanagment.o productmanagment.o fileio.o
	$(CC) -o server server.o server_menus.o statistics.o usermanagment.o productmanagment.o fileio.o

server.o: server.c
	$(CC) $(CFLAGS)	-c server.c

server_menus.o: server_menus.c
	$(CC) $(CFLAGS)	-c server_menus.c

statistics.o: statistics.c
	$(CC) $(CFLAGS)	-c statistics.c

usermanagment.o: usermanagment.c
	$(CC) $(CFLAGS)	-c usermanagment.c

productmanagment.o: productmanagment.c
	$(CC) $(CFLAGS)	-c productmanagment.c

fileio.o: fileio.c
	$(CC) $(CFLAGS)	-c fileio.c

clean:
	rm -rf *.o
