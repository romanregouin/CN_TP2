CC = gcc
CFLAGS =-g -O0 -Wall -Werror
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXE = codeurHamming

all: $(EXE)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

codeurHamming : codeurHamming.o
	$(CC) $(CFLAGS) -o $@ $^

codeurHamming.o : matrice.h

.PHONY : clean

clean:
	rm -f $(EXE) $(OBJ)
