#include "skip_list.h"

#include <stdlib.h>
#include <stdio.h>

int
main() {
	int i, j;
	int *array;
	splt_head_t *head;
	splt_node_t *node;

	array = (int *)malloc(sizeof(int) * 30);

	if (array == NULL) {
		printf("create array fail");
		return -1;
	}

	head = skip_list_init();

	if (head == NULL) {
		free(array);
		return 0;
	}

	srand((unsigned)time(NULL));
	for (i = 0; i < 30; i++) {
		array[i] = i;
		skip_list_insert(head, &array[i]);
	}	

	printf("\n");
	for (i = head->high - 1; i >= 0; i--) {
		printf("high:%d\t", i + 1);

		node = head->next[i];

		while (node != NULL) {
			printf("%d\t",*((int *)(node->value)));
			node = node->next[i];
		}
		printf("\n");
	}

	node = skip_list_find(head, &array[7]);

	printf("node:high[%d],value[%d]\n",node->high, *((int *)(node->value)));

	skip_list_remove_n(head,node);


	printf("\n");
	for (i = head->high - 1; i >= 0; i--) {
		printf("high:%d\t", i + 1);

		node = head->next[i];

		while (node != NULL) {
			printf("%d\t",*((int *)(node->value)));
			node = node->next[i];
		}
		printf("\n");
	}

	skip_list_destroy(head);

	return 0;
}
