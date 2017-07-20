// SelfBalancingTrees.cpp
/*
Rules for RedBlack Trees:
1. Every node is either red or black
2. The root is always black
3. there are never two adjacent red nodes
4. the black depth is the same to any leaf node
*/

#include "stdafx.h"
#include <vector>

#define RED 1
#define BLACK 0
#define LEFT 0
#define RIGHT 1

struct rbnode {
	int val;
	struct rbnode* left = NULL;
	struct rbnode* right = NULL;
	struct rbnode* parent = NULL;
	unsigned short color = RED;
	short side = -1;
};

void rotate(rbnode* x, rbnode* p, rbnode* g, rbnode* u, int side) {
	if (side != LEFT && side != RIGHT) {
		return;
	}
	if (side == LEFT) {
		g->left = p->right;
		p->right = g;
		p->color = BLACK;
		g->color = RED;
		p->side = g->side;
		g->side = RIGHT;
	}
	else { //Right side rotation
		g->right = p->left;
		p->left = g;
		p->color = BLACK;
		g->color = RED;
		p->side = g->side;
		g->side = LEFT;
	}
}

void insert(struct rbnode* root, int value) {
	/*
	recoloring first, if recoloring doesn't work then must reorder
	1. BST insertion normally, new node color: RED
	2. if node is root, change color to black. return.
	3. if parent is RED, or newnode is not root
		a.if uncle is red
			1. uncle & parent = black
			2. grandparent = red
			3. new x = grandparent and recurse
		b.if uncle is black
			LL: 
			LR: 
			RL: 
			RR: 
	*/

	//creating new node to be added
	struct rbnode* x = new struct rbnode;
	x->val = value;

	//finding position in tree to add
	rbnode* traverser = root;
	short side = -1;
	while (traverser != NULL) {
		x->parent = traverser;
		if (value < traverser->val) {
			traverser = traverser->left;
			side = LEFT;
		}
		else {
			traverser = traverser->right;
			side = RIGHT;
		}
	}
	
	//Adding node to tree
	if (side == LEFT) {
		x->side = LEFT;
		x->parent->left = x;
	}
	else {
		x->side = RIGHT;
		x->parent->right = x;
	}

	//fixing
	while (x != NULL) {
		rbnode* p;
		rbnode* g;
		rbnode* u;
		p = x->parent;
		if (p != NULL) g = p->parent;
		else g = NULL;
		if (g != NULL) {
			if (p->side == LEFT) {
				u = g->right;
			}
			else {
				u = g->left;
			}
		}
		
		//Root case
		if (p == NULL) {
			//x-is-root case
			x->color = BLACK;
			return;
		}

		if (g == NULL) {
			x = g;
		}
		else if (g != NULL && p->color == RED) {
			//Recoloring case first
			if (p->color == RED && u->color == RED) {
				p->color = BLACK;
				u->color = BLACK;
				g->color = RED;
				x = g;
				//perform loop again
			}
			else {			//reordering case next
				if (p->side == LEFT) { //First LEFT
					if (x->side == RIGHT) { //Second RIGHT
						//Must prerotate then perform regular LEFT side rotation
						p->right = x->left;
						x->left = p;
						g->left = x;
						x->side = LEFT;
						rotate(p, x, g, u, LEFT);
						//No need to reassign x at this point
					}
					else {
						rotate(x, p, g, u, LEFT);
						x = p; //assign x to topmost position
					}
				}
				else { //First RIGHT
					if (x->side == LEFT) { //Second LEFT
						//Must prerotate then perform regular RIGHT side rotation
						p->left = x->right;
						x->right = p;
						g->right = x;
						x->side = RIGHT;
						rotate(p, x, g, u, RIGHT);
					}
					rotate(x, p, g, u, RIGHT);
					x = p; //assign x to topmost position
				}
			}
		}
	}
}


int main()
{
    return 0;
}

