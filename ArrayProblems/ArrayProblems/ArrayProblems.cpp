// ArrayProblems.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include <string>

char* addBinaryStrings(char* a, char* b) {
	//Establishing lengths
	int lena = std::strlen(a);
	int lenb = std::strlen(b);
	int len = 0;
	if (lena > lenb) len = lena;
	else len = lenb;

	//create a string to be returned that is by default, will realloc if overflow doesn't occur
	char* sum = (char*)malloc(sizeof(char) * (len + 2));

	unsigned short carry = 0;
	unsigned short added = 0;
	int i = len - 1;
	sum[len + 1] = '\0';
	//replace into a;
	while (i >= 0) {
		unsigned short first = a[i] - '0';
		unsigned short second = b[i] - '0';
		added = first ^ second ^ carry; //1,1,1 = 1; 1 0 1 = 0; 1 0 0 = 1; and any combination of those hold
		(first + second + carry > 1) ? carry = 1 : carry = 0; //Carry conditions
		sum[i + 1] = (char)(added + '0');
		i--;
	}
	if (carry == 0) {
		char* fixedptr = (char*)(&(sum[1]));
		fixedptr = (char*)realloc(sum, len + 1);
		free(sum);
		return fixedptr;
	}
	else {
		sum[0] = (char)(carry + '0');
		return sum;
	}
}

int main()
{
	char* a = "011";
	char* b = "011";
	char* addition = addBinaryStrings(a, b);
    return 0;
}

