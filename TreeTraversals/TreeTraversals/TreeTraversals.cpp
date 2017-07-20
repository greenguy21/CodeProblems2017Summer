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
	std::stack<struct treeNode*> nstack;
	std::stack<struct treeNode*> pstack;
	struct treeNode* curr = node;
	int count = 0;
	bool stackvar = true;
	while (stackvar || curr != NULL) {
		if (curr == NULL) {
			if (nstack.top() == NULL) {
				nstack.pop();
				curr = nstack.top();
				nstack.pop();
				printf("%d, ", curr->val);
				pstack.push(curr);
			}
			//Top of nstack != NULL
			curr = nstack.top();
			nstack.pop();
		}
		else {
			if (!pstack.empty() && pstack.top() == curr->right) {
				printf("%d, ", curr->val);
				pstack.push(curr);
				if (!nstack.empty()) {
					curr = nstack.top();
					nstack.pop();
				}
				else curr = NULL;
			}
			else {
				nstack.push(curr);
				nstack.push(curr->right);
				curr = curr->left;
			}
		}
		stackvar = !nstack.empty();
	}
	printf("\n");
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

