src:=skip_list.c main.c
objs:=$(patsubst %.c,%.o,$(src))

target:=libskip_list.so main

all:$(target)

libskip_list.so:$(objs)
	gcc -g -shared -fpic -o $@ $^

main:main.c
	gcc -g  -o $@ $^ -L. -lskip_list 

%.o:%.c
	gcc -g -c -o $@ $<	

clean:
	rm -rf $(objs) $(target) 
