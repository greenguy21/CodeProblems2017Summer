// TreeTraversals.cpp : Defines the entry point for the console application.
//
//Numbers to be added to tree:  34 4 14 43 39 27 22 16 41 31

#include "stdafx.h"
#include <stack>
#include <queue>

struct treeNode {
	int val = 0;
	struct treeNode* left = NULL;
	struct treeNode* right = NULL;
};

struct treeNode * ROOT;

struct treeNode* insert(int val, struct treeNode* node) {
	if (node == NULL) {
		struct treeNode* temp = new struct treeNode;
		temp->val = val;
		return temp;
	}
	else {
		//printf("%d, ", node->val);
		if (val >= node->val) {
			node->right = insert(val, node->right);
		}
		else {
			node->left = insert(val, node->left);
		}
	}
	return node;
}

void preorder(struct treeNode* node) {
	if (node == NULL) {
		return;
	}
	else {
		printf("%d ",node->val);
		preorder(node->left);
		//printf("/");
		preorder(node->right);
		//printf("\\");
	}
}

void postorder(struct treeNode* node) {
	if (node == NULL) {
		return;
	}
	else {
		postorder(node->left);
		postorder(node->right);
		printf("%d ", node->val);
	}
}

void inorder(struct treeNode* node) {
	if (node == NULL) {
		return;
	}
	else {
		inorder(node->left);
		printf("%d ", node->val);
		inorder(node->right);
	}
}

void inorderInline(struct treeNode* node) {
	printf("inorder:\n");
	
	//Initializing and priming the stack
	std::stack<struct treeNode*> nstack;
	struct treeNode* curr = node;
	int count = 0;
	bool stackvar = true;
	while (stackvar || curr != NULL) {
		if (curr == NULL) {
			//go to top of stack
			curr = nstack.top();
			nstack.pop();
			//print top of stack
			printf("%d, ", curr->val);
			//go to right of current value;
			curr = nstack.top(); //right sibling
			nstack.pop();
		}
		else {
			//Default action: go left
			nstack.push(curr->right);
			nstack.push(curr);
			curr = curr->left;
		}
		stackvar = !nstack.empty();
	}
}

void postorderInline(struct treeNode* node) {
	printf("postorder:\n");

	//Initializing and priming the stack
	std::stack<struct treeNode*> nstack; //maintain traversal history for backtracking
	struct treeNode* lastPrinted = NULL; //maintain the last visited node to handle revisitation cases
	struct treeNode* curr = node; //maintains current node of concern
	bool stackvar = true; //variable that maintains the empty state of the nstack. Necessary for proper function as of now. Could be optimized out.
	while (stackvar || curr != NULL) { //End case is the stack is empty AND the current node is NULL
		if (curr == NULL) { //Case where traversal has reached a NULLterminated leaf node
			if (nstack.top() == NULL) { //When the traversal has reached a leaf, 
										//it should be that the right node added to the tree is NULL, 
										//in which case, printing should occur
				nstack.pop(); //Remove the NULL
				curr = nstack.top(); //Set the current node to be the Leaf node (the next node on the stack)
				nstack.pop(); //Remove that node from the stack.
				printf("%d, ", curr->val); //Print the value (could be replaced by whatever ordered recording functionality is desired)
				lastPrinted = curr; //Maintain that the last 

			}
			curr = nstack.top(); //Set up state (current node) for next step
			nstack.pop(); //remove current node from stack
		}
		else {
			if (lastPrinted != NULL &&  lastPrinted == curr->right) { //Case where node's children have already been printed and node needs to be printed
				printf("%d, ", curr->val); //Print current node
				lastPrinted = curr; //maintain last printed node
				if (!nstack.empty()) { //check that current node isn't root node (there is nothing left in the stack to backtrace)
					curr = nstack.top(); //set new current node
					nstack.pop(); //remove newly-set current node from stack
				}
				else curr = NULL; //if reached the end of the stack, current must be set to NULL to break out of loop
			}
			else { //Case where current node's children haven't all been printed
				nstack.push(curr); //maintain backtracking stack and continue traversal
				nstack.push(curr->right); //Important to add the sibling of the node to-be visited last to stack for proper post-order functionality
				curr = curr->left; //traverse left (left-first post-order traversal) to reach leaf nodes
			}
		}
		stackvar = !nstack.empty(); //maintain the stack.empty check variable
	}
	printf("\n"); //finish up traversal and printing with a newline for good measure.
}

void BFT(struct treeNode* node) {
	std::queue<struct treeNode*> q;
	q.push(node);
	printf("BFS of tree: ");
	while (!q.empty()) {
		struct treeNode* currNode = q.front();
		q.pop();
		if (currNode->left != NULL) q.push(currNode->left);
		if (currNode->right != NULL) q.push(currNode->right);
		printf("%d, ", currNode->val);
	}
	printf("\n");
}

int main()
{
	int arr[] = {34, 22, 27, 4, 14, 41, 43, 39, 16, 31};
	struct treeNode* root = NULL;
	for (int i : arr) {
		printf("inserting %d \n", i);
		root = insert(i, root);
		//printf("\n");
	}
	printf("\n");
	preorder(root);
	printf("\n");
	postorder(root);
	printf("\n");
	inorder(root);
	printf("\n");
	inorderInline(root);
	printf("\n");
	postorderInline(root);
	BFT(root);
    return 0;
}

