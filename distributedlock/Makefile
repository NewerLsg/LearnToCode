INCLUDE=-I./src

LIBS=-lhiredis 

VPATH=src

SOURCES= main.c \
		 dlock.c

OBJECTS=$(SOURCES:.c=.o)

OUTPUT=main

all:$(OUTPUT)

.SUFFIXES:.c .o
.c.o:
	gcc -g -c  $(INCLUDE) $(filter %c, $^)

$(OUTPUT):$(OBJECTS)
	gcc -g  $(INCLUDE) -o $@ $^ $(LIBS)

clean:
	rm *.o
	rm  $(OUTPUT)
