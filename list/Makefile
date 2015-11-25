DEBUG=true

CC=gcc

ifeq ($(DEBUG),true)
	CFLAGS = -c -Wall -g
else
	CFLAGS = -c -Wall
endif

EXE=list

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
DEP=$(SOURCES:.c=.h)

all: $(EXE)

list: $(OBJ)
	@$(CC) -o $@ $^ 

main.o: blist.h

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o $(EXE)

