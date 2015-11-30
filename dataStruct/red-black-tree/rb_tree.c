#include <stdio.h>
#include <unistd.h>

#include "rb_tree.h"

static void rbt_lroute(rbt_t *rbt,rbt_node_t *node);
static void rbt_rroute(rbt_t *rbt,rbt_node_t *node);

void rbt_insert(rbt_t *rbt, rbt_node_t *node,rbt_node_t *sentiel){

	//插入节点
	rbt->insert(rbt, node,sentiel);

	//node非root节点(保证了有父节点),父节点为红色	
	while(node != rbt->root && rbt_is_red(node->parent)){
		//叔节点
		rbt_node_t *tmp = NULL;
		if(node->parent == rbt_lchild(node->parent->parent)){

			tmp = rbt_rchild(node->parent->parent);	

			//均为红色			
			if(rbt_is_red(tmp)){
				rbt_set_black(node->parent);	
				rbt_set_black(tmp);	
				rbt_set_red(node->parent->parent);
				node = node->parent->parent;
			}else{
				//此节点为父节点的右节点，需要左旋调整
				if( node == rbt_rchild(node->parent) ){
					rbt_lroute(rbt,node);	
				}else{
					node = node->parent;
				}
				//右旋调整
				rbt_set_black(node);		
				rbt_set_red(node->parent);
				rbt_rroute(rbt,node);
			}	

		}else{

			tmp = rbt_lchild(node->parent->parent);

			//均为红色			
			if(rbt_is_red(tmp)){
				rbt_set_black(node->parent);	
				rbt_set_black(tmp);	
				rbt_set_red(node->parent->parent);
				node = node->parent->parent;
			}else{
				//此节点为父节点的左节点，需要右旋调整
				if( node == rbt_lchild(node->parent) ){
					rbt_rroute(rbt,node);	
				}else{
					node = node->parent;	
				}
				//左旋调整
				rbt_set_black(node);		
				rbt_set_red(node->parent);
				rbt_lroute(rbt,node);
			}
		
		}

	}
	
	rbt_set_black(rbt->root);

	return;
}

void rbt_lroute(rbt_t *rbt, rbt_node_t *node){
	
	//保存节点的左子树	
	rbt_node_t *tmp = rbt_lchild(node);
	
	if(tmp){
		//节点左子树指向节点的父节点
		tmp->parent = node->parent;
	}	

	//节点的左子树指向其父节点
	node->lchild = node->parent;	

	//父节点的右子树指向tmp
	node->parent->rchild = tmp;
	
	//节点的父节点指向原祖父节点	
	if(node->parent->parent){
		node->parent = node->parent->parent;	
		node->parent->rchild = node;
	}else{
		node->parent = NULL;
		rbt->root = node;	
	}

	//原父节点(现节点左子树)的父节点指向节点
	node->lchild->parent = node;
	
	return;
}

void rbt_rroute(rbt_t *rbt, rbt_node_t *node){
	rbt_node_t *tmp = rbt_rchild(node);
	
	if(tmp){
		tmp->parent = node->parent;
	}	

	node->rchild = node->parent;	

	node->parent->lchild = tmp;
	
	if(node->parent->parent){
		node->parent = node->parent->parent;	
		node->parent->lchild = node;
	}else{
		node->parent = NULL;
		rbt->root = node;
	}

	node->rchild->parent = node;
	
}
