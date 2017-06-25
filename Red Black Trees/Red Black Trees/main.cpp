//
//  main.cpp
//  Red Black Trees
//
//  Created by Pranay Shoroff on 6/4/17.
//  Copyright © 2017 Pranay Shoroff. All rights reserved.
//

/*
 The 4 rules of red black trees:
 -Every node is either red or black
 -root is always black
 -there are no two adjacent red nodes
 -every path from root to null has the same number of black nodes
 */

#include <iostream>

const int RED = 1;
const int BLACK = 0;

struct rbnode{
    int color;
    int value;
    struct rbnode * left;
    struct rbnode * right;
    struct rbnode * parent;
};

//method declaration space:
void insert(rbnode * root, int val);

void arrange(rbnode * x, rbnode * parent, rbnode * uncle, rbnode * gp){
    if (x == NULL) return;
    parent = x->parent;
    if (parent != NULL) gp = parent->parent;
    if (gp != NULL){
        if (parent->value >= gp->value) uncle = gp->left;
        else uncle = gp->right;
    }
}

void insert(rbnode * root, int val){
    
    //Creating node to be inserted
    struct rbnode * nnode = new rbnode;
    nnode->color = RED;
    nnode->value = val;
    nnode->left = NULL;
    nnode->right = NULL;
    nnode->parent = NULL;
    
    //finding point of insertion:
    struct rbnode * pnode = root; //Node to creep rbtree
    
    bool added = false;
    while(pnode->left != NULL || pnode->right != NULL){
        if (pnode->value >= val){
            if (pnode->right == NULL){
                pnode->right = nnode;
                nnode->parent = pnode;
                added = true;
            }
            pnode = pnode->right;                       //Update pnode
        } else {
            if (pnode->left == NULL){
                pnode->left = nnode;
                nnode->parent = pnode;
                added = true;
            }
            pnode = pnode->left;
        }
    }
    
    //Check if tree was empty to begin with,
    //if so add as root, color black, and exit;
    if (added == false){
        root = nnode;
        root->color = BLACK;
        return;
    }
    
    struct rbnode * parent = NULL; //Node to keep track of parent node
    struct rbnode * uncle = NULL; //Node to keep track of uncle node
    struct rbnode * gparent = NULL; //Node to keep track of grandparent node
    
    arrange(nnode, parent, uncle, gparent);
    
    while(nnode != NULL){
        //Step 2: Check if new node is root:
        if (nnode == root){
            nnode->color = BLACK;
            nnode = NULL;
            break;
        }
        
        //Step 3: Check case and absolve
        //Check if parent is root
        if (parent == root){
            nnode = parent;
            break;
        }
        
        //check if parent is red
        if (parent->color == RED && nnode->color == RED){ //Double RED case
            //First check color of uncle
            if (uncle->color == RED){ //This assumes grandparent & uncle != null && grandparent color == black,
                //All that needs to be done is recoloring;
                gparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                nnode = gparent; //set grandparent as new nnode for next round
            } else {
                
                //Grandparent color is black, so relative placement of nnode needs to be found
                //Recoloring + rotations must be done:
                struct rbnode * ggp = gparent -> parent;
                
                if (parent->value < gparent->value && nnode->value < parent->value){ //Left Left case
                    if (ggp != NULL){ //make sure ggparent doesn't lose pointer if ggp exists
                        if (gparent->value < ggp->value) ggp->left = parent;
                        else ggp->right = parent;
                    }
                    gparent->left = parent->right;
                    parent->right = gparent;
                    
                    //recoloring:
                    parent->color = BLACK;
                    gparent->color = RED;
                    nnode = parent;
                } else if (parent->value < gparent->value && nnode->value >= parent->value){ //Left Right case
                    //Rotate parent/nnode first:
                    gparent->left = nnode;
                    parent->right = nnode->left;
                    nnode->left = parent;
                    
                    //perform LL rotations:
                    if (ggp != NULL){ //make sure ggparent doesn't lose pointer if ggp exists
                        if (gparent->value < ggp->value) ggp->left = nnode;
                        else ggp->right = nnode;
                    }
                    gparent -> left = nnode->right;
                    nnode -> right = gparent;
                    //Recolor:
                    gparent->color = RED;
                    nnode->color = BLACK;
                    //Leave nnode as new nnode
                } else if (parent->value >= gparent->value && nnode->value < parent->value){ //Right Left case
                    gparent -> right = nnode;
                    parent->left= nnode->right;
                    nnode->right = parent;
                    
                    if (ggp != NULL){ //make sure ggparent doesn't lose pointer if ggp exists
                        if (gparent->value < ggp->value) ggp->left = nnode;
                        else ggp->right = nnode;
                    }
                    gparent->right = nnode->left;
                    nnode->left = gparent;
                    //Recolor:
                    gparent->color = RED;
                    nnode->color = BLACK;
                    //nnode remains as new nnode
                } else { // if (parent->value >= gparent->value && nnode->value >= parent->value) //Right Right case
                    //The absolving process is very similar to the left left case
                    if (ggp != NULL){ //make sure ggparent doesn't lose pointer if ggp exists
                        if (gparent->value < ggp->value) ggp->left = parent;
                        else ggp->right = parent;
                    }
                    gparent->right = parent->left;
                    parent->left = gparent;
                    //Recolor:
                    gparent->color = RED;
                    parent->color = BLACK;
                    nnode = parent;
                }
            }
            arrange(nnode, parent, uncle, gparent);
        }
        
    }
    
    
    
    //Check parent node color if reorganization can happen
    while (parent != NULL && parent->color == RED){
        //Check heirarchy:
        if (gparent == NULL)
        //Red Uncle case:
        if (uncle != NULL && uncle->color==RED){
            parent->color = BLACK;
            uncle->color = BLACK;
            gparent->color = RED;
            
            //reorganize:
            nnode = gparent;
            parent = nnode->parent;                                             //Set Parent
            if (parent != NULL) gparent = parent->parent;                       //Set Grandparent
            if (gparent != NULL){                                               //Set Uncle
                if (parent->value >= gparent->value) uncle = gparent->left;
                else uncle = gparent->right;
            }
        }
        
        if (gparent->value > parent->value && parent->value > nnode->value){ // Left Left case
            
        } else if(gparent->value > parent->value && parent->value <= nnode->value){ // Left Right case
            
        } else if (gparent->value <= parent->value && parent->value > nnode->value){ // Right Left case
            
        } else if (gparent->value <= parent->value && parent->value <= nnode->value){ // Right Right case
            
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
