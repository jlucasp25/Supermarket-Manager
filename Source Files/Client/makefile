##########################################
#         MakeFile para Client           #
#   		 Projecto LABC               #
#	João Lucas Pires e Solange Sampaio   #
#        201606617 e 201603610           #
##########################################

# "make" para compilar
# "make clean" para apagar ficheiros *.o

CC=gcc
CFLAGS=-g -Wall

all: client

client: client.o clientmenus.o statistics.o fileio.o balance.o shoppinglist.o usermanagment.o
	$(CC) -o client client.o clientmenus.o statistics.o fileio.o balance.o shoppinglist.o usermanagment.o

client.o: client.c
	$(CC) $(CFLAGS)	-c client.c

clientmenus.o: clientmenus.c
	$(CC) $(CFLAGS)	-c clientmenus.c

statistics.o: statistics.c
	$(CC) $(CFLAGS)	-c statistics.c

fileio.o: fileio.c
	$(CC) $(CFLAGS)	-c fileio.c

balance.o: balance.c
	$(CC) $(CFLAGS)	-c balance.c

shoppinglist.o: shoppinglist.c
	$(CC) $(CFLAGS)	-c shoppinglist.c

usermanagment.o: usermanagment.c
	$(CC) $(CFLAGS)	-c usermanagment.c

clean:
	rm -rf *.o
