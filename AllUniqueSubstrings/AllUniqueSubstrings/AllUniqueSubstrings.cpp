// AllUniqueSubstrings.cpp :
/*This program computes the number of and prints all unique substrings within a string*/

#include "stdafx.h"
#include <unordered_map>
#include <string>
#include <iostream>

//Node structure for trie
struct trieNode {
	char val = 0;
	std::unordered_map<char, struct trieNode *> kids;
	bool isWord = false;
};

//This function takes a string, and the root of a trie
//inserts string into trie
void insertWord(std::string s, struct trieNode* root) {
	std::string::iterator it = s.begin();
	struct trieNode* curr = root;
	while (it != s.end()) {
		if (curr->kids.find(*it) == curr->kids.end()) {
			curr->kids[*it] = new struct trieNode;
			curr->kids[*it]->val = *it;
		}
		curr = curr->kids[*it];
		it++;
	}
	curr->isWord = true;
}

//Prints all words found within trie
int printTrie(struct trieNode* node, int count, std::string curr) {
	int newCount = count;
	if (node->isWord) {
		printf("\"%s\", ", curr.c_str());
		newCount++;
	}
	if (node->kids.empty() == true) {
		return newCount;
	}
	else {

		for (auto c : node->kids) {
			newCount = printTrie(c.second, newCount, curr + c.first);
		}
		return newCount;
	}
	return newCount;
}

//main calling function
//takes word to process, analyze, and print all substrings 
//and count of number of unique substrings
void findSubstrings(std::string word) {
	struct trieNode* root = new struct trieNode;
	for (int i = 0; i < (int)word.size(); i++) {
		for (int j = 0; j <= (int) word.size()-i; j++) {
			insertWord(word.substr(i, j), root);
		}
	}
	int count = printTrie(root, 0, "");
	printf("\ncount:%d\n", count);
}


int main()
{
	std::string sample;
	printf("Please enter a word to be processed (no whitespace): ");
	std::getline(std::cin, sample);
	findSubstrings(sample);
    return 0;
}

