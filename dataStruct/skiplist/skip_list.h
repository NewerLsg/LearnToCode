#ifndef SKIP_LIST_H
#define SKIP_LIST_H


#define MAXLEVEL 5

typedef struct skip_list_s splt_head_t;

typedef struct skip_list_s splt_node_t;

struct skip_list_s{
	unsigned int 		high;	
	void 				*value;
	struct skip_list_s  *next[0];
};

splt_head_t *skip_list_init();

splt_node_t *skip_list_insert(splt_head_t *head, void *value);

void skip_list_remove_v(splt_head_t *head, void *value);

void skip_list_remove_n(splt_head_t *head, splt_node_t *node);

splt_node_t *skip_list_find(splt_head_t *head,void *value);

void skip_list_destroy(splt_head_t *head);

#endif
