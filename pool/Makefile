
src:=tpool.c main.c
objs:=$(patsubst %.c,%.o,$(src))

target:=libtpool.so main

all:$(target)

libtpool.so:$(objs)
	gcc -g -shared -fpic -o $@ $^

main:main.c
	gcc -g  -o $@ $^ -L. -ltpool -lpthread

%.o:%.c
	gcc -g -c -o $@ $<	

clean:
	rm -rf $(objs) $(target) 
