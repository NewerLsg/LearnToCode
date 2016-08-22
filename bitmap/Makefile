INC = -I.

LIBS =

VPATH = .

OUTPUT = main

SRC = bitmap.c

OBJECTS = $(SRC:.c=.o)

all:$(OUTPUT)

$(OUTPUT):$(OBJECTS)
	gcc -g -o $@ $^

.SUFFIXES: .o .c .so .a

.c.o:
	gcc -g $(INC) -c $^

clean:
	rm $(OUTPUT) $(OBJECTS)
