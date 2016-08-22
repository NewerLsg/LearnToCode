#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define set_bit(bit_map,index,val) \
	bit_map[index/8] |= (val << (index % 8))

#define get_bit(bit_map,index) \
	bit_map[index/8] & (1 << (index % 8))

int init_bitmap(char** bit_map, unsigned int max);

int 
main(){
	char* bit_map = NULL;
	unsigned int *array = (unsigned int *)  malloc(1000000 * sizeof(int));
	unsigned int *array2 = (unsigned int *) malloc(1000000 * sizeof(int));
	
	srand(time(NULL));
	
	int i = 0;
	for (i = 0; i < 1000000; i++) {
		array[i] = rand() % 1000000;
	}
	
	for (i = 0; i < 1000000; i++) {
		if (i%10 == 0) 
			array2[i] = array[i];
		else
			array2[i] = rand()/1000000;
	}

	init_bitmap(&bit_map, 1000000);
	
	for (i = 0; i < 1000000 ; i++) {
		set_bit(bit_map, array[i], 1);	
	}


	for (i = 0; i < 1000000; i++) {
		if (get_bit(bit_map, array2[i])) {
			printf("val:[%d]\n", array2[i]);
		}
	}
	return 0;
}

int 
init_bitmap(char** bit_map, unsigned int max) {
	int len = max / 8 + (max % 8 > 0? 1 : 0);	
	*bit_map = (char *) malloc(len);

	if (*bit_map == NULL) return -1;

	memset(*bit_map, 0, len);

	return 0;
}
