#include <stdio.h>
#include <stdlib.h>

#include "rb_tree.h"


void node_insert(rbt_t *rbt, rbt_node_t *node, rbt_node_t *sentinel);
void printRbtree(rbt_t *rbt,rbt_node_t *sentinel);

int 
main(int argc,char *argv[]){
	rbt_t *first_rbt;
	
	first_rbt = (rbt_t *)malloc(sizeof(rbt_t));
	
	if(first_rbt == NULL){
		printf("alloc fail.");		
		return;
	}

	rbt_node_t sentinel;
	rbt_set_black((rbt_node_t *)(&sentinel));
	sentinel.rchild = &sentinel;
	sentinel.lchild = &sentinel;

	rbt_node_insert insert_fn = &node_insert;	

	rbt_init(first_rbt,insert_fn,(rbt_node_t *)&sentinel);		
	
	int i = 0;
	for(; i < 10; i++){
		int *key = (int *)malloc(sizeof(int));		
		*key = i;
		rbt_node_t *node = (rbt_node_t *)malloc(sizeof(rbt_node_t));
		node->key = key;
		rbt_insert(first_rbt,node,(rbt_node_t *)&sentinel);
		printRbtree(first_rbt,(rbt_node_t*)&sentinel);
		printf("\n");
	}
	
	printRbtree(first_rbt,(rbt_node_t*)&sentinel);

	for(;;){}

	return ;

}

void node_insert(rbt_t *rbt, rbt_node_t *node, rbt_node_t *sentinel)
{
	rbt_node_t *p; 
	rbt_node_t *tmp = rbt->root;	
	
	if( rbt->root == sentinel){
		rbt_set_black(node);
		node->lchild = sentinel;
		node->rchild = sentinel;
		rbt->root = node;
		return ;
	}

	while(tmp){
		p = *((int *)node->key) < *((int*)tmp->key)?rbt_lchild(tmp):rbt_rchild(tmp);

		if(p == sentinel){
			break;		
		}
		tmp = p;
	}
	if(*((int *)node->key) < *((int*)tmp->key))	{
		tmp->lchild = node;	
	}else{
		tmp->rchild = node;
	}

	node->lchild = sentinel;
	node->rchild = sentinel;
	node->parent = tmp;
	rbt_set_red(node);
}

void preTree(rbt_node_t *root,rbt_node_t *sentinel){
	if(root == sentinel) return ;
				
	if(rbt_lchild(root)){
		preTree(rbt_lchild(root),sentinel);
	}
	
	printf("k:%d,c:%d\t",*((int *)root->key),(u_int)root->color);

	
	if(rbt_rchild(root)){
		preTree(rbt_rchild(root),sentinel);		
	}
	return;
}

void printRbtree(rbt_t *rbt,rbt_node_t *sentinel){
	rbt_node_t *node = rbt->root;		
	if(node != sentinel){
		printf("root:k:%d,c:%d\t\t",*((int *)node->key),(u_int)node->color);
		preTree(node,sentinel);
	}
	return;
}

