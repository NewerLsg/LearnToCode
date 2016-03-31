INCLUDE=

LIBS=-ldl

VPATH=


SOURCES=testlib.c \
		main.c

OBJECTS=$(SOURCES:.c=.o)

OUTPUT=main

DLIB=libtestlib.so

all:$(DLIB) $(OUTPUT)

.SUFFIXES:.c .o
.c.o:
	gcc $(INCLUDE) -c $(filter %.c, $^)

$(DLIB):testlib.o
	gcc -fPIC -shared -o $@ $^

$(OUTPUT):main.o
	gcc  -rdynamic -o $@ $^ -L./ -ltestlib $(LIBS)


clean:
	rm *.o *.so
	rm $(OUTPUT)


