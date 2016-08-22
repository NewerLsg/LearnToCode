INCLUDES=-I./include

LIBS=

CFLAGS=-g

VPATH=src

SOURCES=main.c \
		glog.c \
		test.c

OBJECTS=$(SOURCES:.c=.o)

OUTPUT=main

all:$(OUTPUT)

.SUFFIXES:.o .c

.c.o:
	gcc $(CFLAGS) -c $(INCLUDES)  $(filter %.c, $^)

$(OUTPUT):$(OBJECTS)
	gcc $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

clean:
	rm *.o
	rm $(OUTPUT)
