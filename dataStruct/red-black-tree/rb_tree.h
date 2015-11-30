#ifndef RB_TREE_H
#define RB_TREE_H

#include <stdint.h>
#include <sys/types.h>
//"亲戚"节点操作
#define rbt_parent(node) 		((node)->parent)
#define rbt_lchild(node) 		((node)->lchild)
#define rbt_rchild(node) 		((node)->rchild)

//节点颜色以判断
#define rbt_set_red(node) 		((node)->color = 0x01)
#define rbt_set_black(node) 	((node)->color = 0x02)
#define rbt_is_red(node)		((node)->color == 0x01?1:0)
#define rbt_is_black(node)		((node)->color == 0x02?1:0)

#define rbt_init(rbt,insert_fn,sentiel) 		\
		rbt->root = sentiel; 				\
		rbt->insert = insert_fn	

#define rbt_node_free(node) 			\
		free(node->key);				\
		free(node->value);				\
		free(node)						

typedef struct rbt_node_s rbt_node_t;
typedef struct rbt_s rbt_t;

struct rbt_node_s{
	void 		*key;	
	void 		*value;
	u_char 		color;	
	rbt_node_t  *parent;
	rbt_node_t  *lchild;
	rbt_node_t  *rchild;
};

typedef void (*rbt_node_insert)(rbt_t *rbt, rbt_node_t *node,rbt_node_t *sentiel);

struct rbt_s{
	rbt_node_t *root;		
	rbt_node_insert insert;
};

void rbt_insert(rbt_t *rbt, rbt_node_t *node,rbt_node_t *sentiel);

#endif
