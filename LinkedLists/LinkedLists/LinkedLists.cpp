// LinkedLists.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <ctime>


struct listnode {
	int val;
	listnode* next = NULL;
};

//returns pointer to root value
listnode* insert(int n, listnode * root) {
	listnode * newnode = new listnode;	//There is no need to use the struct keyword upon declaration 
										//unless there is a conflict in naming between a function and a struct type
	newnode->val = n;
	
	if (root == NULL) {
		return newnode;
	}

	listnode * curr = root;
	listnode * prev = NULL;
	while (curr != NULL && curr->val < n) {
		prev = curr;
		curr = curr->next;
	}
	if (prev == NULL) {
		newnode->next = curr;
		return newnode;
	}
	newnode->next = curr;
	prev->next = newnode;
	return root;
}

//removes the first occurrence of a node with value n
//returns 0 if successful, -1 if error encountered or value could not be found;
int remove(int n, listnode* root) {
	listnode* curr = root;
	listnode* prev = NULL;
	while (curr != NULL) {
		if (curr->val == n) {
			break;
		}
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL) {
		return -1;
	}
	if (prev == NULL) {
		root = curr->next;
		return 0;
	}
	prev->next = curr->next;
	delete(curr);
	return 0;
}

void printlist(listnode* root) {
	listnode* curr = root;
	while (curr != NULL) {
		printf("%d, ", curr->val);
		curr = curr->next;
	}
	printf("\n");
}


int main()
{
	srand((unsigned)time(0));
	listnode * root = insert(1, NULL);
	for (int i = 1; i < 10; i++) {
		root = insert((rand() % 50 + 1), root);
	}
	printlist(root);
    return 0;
}

