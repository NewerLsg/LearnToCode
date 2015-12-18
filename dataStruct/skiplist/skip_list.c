#include "skip_list.h"

#include<stdlib.h>
#include<sys/time.h>

#define isBiger(a,b,type) \
	(*((type *)(a)) > *((type *)(b)) ? 1 : 0)

#define isEqual(a,b,type) \
	(*((type *)(a)) ==  *((type *)(b)) ? 1 : 0)

splt_head_t *
skip_list_init() {
	int 			i;
	splt_head_t 	*head;
	
	head  = (splt_head_t *)malloc(sizeof(splt_head_t) + MAXLEVEL * sizeof(splt_node_t *));

	if (head == NULL) {
		return NULL;
	}

	head->high = 1;
	head->value = NULL;
	
	for (i = 0; i< MAXLEVEL; i++) {
		head->next[i] = NULL;
	}	
		
	return head;
}


static splt_node_t *
skip_list_node_init(void *value, unsigned int high) {
	int 			i;
	splt_node_t 	*node;	
	
	high = (high == 0) ? 1: (high);

	node = (splt_node_t *)malloc(sizeof(splt_node_t)+ high * sizeof(void *));
	if (node == NULL) {
		return NULL;
	}
	
	for (i = 0; i < high; i++) {
		node->next[i] = NULL;	
	}

	node->high  	= high;	
	node->value 	= value;

	return node;
}


splt_node_t *
skip_list_insert(splt_head_t *head, void *value) {
	unsigned int rand_high, base, i;
	unsigned int high; 
	splt_node_t *new_node, *tmp, *pos;

	//获取随机高度,该高度最多比头结点高一层
	
	if (head == NULL) return NULL;

	if (head->high < MAXLEVEL) {
		base = head->high + 1;	
	}else {
		base = head->high;
	}	

//	srand((unsigned)time(NULL));

	rand_high = rand()%base + 1;

	printf("high:%u,base:[%u],rh:[%u]\n",head->high ,base, rand_high);

	//初始化一个节点
	new_node = skip_list_node_init(value, rand_high);

	if (new_node == NULL) {
		return NULL;	
	}

	high = head->high;

	//新节点比头结点高
	if (head->high < new_node->high) {
		head->high = new_node->high;
		head->next[head->high - 1] = new_node;				
	}
	
	pos = head;

	while ((pos!= NULL) && (high > 0)) {

		if (pos->next[high -1] == NULL) {
				if (new_node->high >= high) {
					pos->next[high - 1] = new_node;				
				}

			high--;
			continue;
		}		
		
		tmp = pos->next[high - 1];	

		if (isBiger(tmp->value, new_node->value, int)) {
			new_node->next[high - 1] = tmp;	
			pos->next[high -1] = new_node;
			high--;

		}else {
			pos = pos->next[high - 1];
		}
	}
		
	return new_node;
}

void
skip_list_remove_v(splt_head_t *head, void *value) {
	splt_node_t *node;
	node = skip_list_find(head, value);
	
	if (node != NULL) {
		skip_list_remove_n(head, node);
	}

	return ;
}

void 
skip_list_remove_n(splt_head_t *head, splt_node_t *node) {
	unsigned high;
	splt_node_t *pos,*tmp;
	
	pos = head;
	high = head->high;

	while ((pos!= NULL) && (high > 0)) {

  		if (pos->next[high -1] == NULL) {
			high--;
			continue;
		}		
		
		tmp = pos->next[high - 1];	

		if (isBiger(tmp->value, node->value, int)) {
			high--;	

		}else if(isEqual(tmp->value, node->value, int)) {
			pos->next[high -1 ] = node->next[ high - 1];
			high--;

		}else {
			pos = pos->next[high - 1];
		}
	}
	
	free(node);

	return ;
}

void 
skip_list_destroy(splt_head_t *head) {
	splt_node_t *tmp;

	while (head) {
		tmp = head; 
		head = head->next[0];
		free(tmp);
	}
			
	return ;
}

splt_node_t *
skip_list_find(splt_node_t *head, void *value) {
	unsigned high;
	splt_node_t *pos,*tmp;
	
	pos = head;
	high = head->high;

	while ((pos!= NULL) && (high > 0)) {

  		if (pos->next[high -1] == NULL) {
			high--;
			continue;
		}		
		
		tmp = pos->next[high - 1];	

		if (isBiger(tmp->value, value, int)) {
			high--;	

		}else if(isEqual(tmp->value, value, int)) {
			return tmp;

		}else {
			pos = pos->next[high - 1];
		}
	}

	return NULL;
}
