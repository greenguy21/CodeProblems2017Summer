/*
 * main.c
 *
 *  Created on: May 27, 2017
 *      Author: Pranay
 */
#include <stdio.h>

unsigned int add(unsigned int a, unsigned int b){
	unsigned int sum = 0, carryin = 0, k = 1,temp_a = a, temp_b = b;
	while(temp_a || temp_b){
		unsigned ak = a&k, bk = b&k; // determine the kth bit of a and b

		unsigned carryout = (ak & bk) | (carryin & bk) | (carryin & ak); // determine the carry out

		sum |= (ak ^ bk ^ carryin); // updating the sum with the kth bit

		carryin = carryout<<1, k<<=1, temp_a>>=1, temp_b>>=1;
	}
	return sum;
}

int clearBit(unsigned char num, int index){
	unsigned char mask = (0xFF ^ (0x1<<index));
	return (num & mask);
}

int setBit(unsigned char num, int index){
	unsigned char mask = 0x1<<index;
	return num | mask;
}

int getBit(unsigned char num, int index){
	unsigned char mask = (unsigned char) 0x1<<index;
	return (num&mask ? 1 : 0);
}

void shiftCompare(int num, int numshift){
	int arithShifted = num>>numshift;
	int logiShifted = (unsigned int) num>>numshift;
	printf("num=0x%08x, %d \narithmetic shift:0x%08x, %d \nlogical shift:0x%08x, %d\n\n", num, num, arithShifted, arithShifted, logiShifted, logiShifted);
}

void printBits(unsigned int num, int spacing){
	unsigned int mask = 0x80000000;
	printf("0b: ");
	for(int i = 0; i < sizeof(num)*8; i++){
		int ibit = (num&mask) ? 1 : 0;
		if (i%spacing == 0) printf(" ");
		printf("%u", ibit);
		num<<=1;
	}
	printf("\n");
}

int main(int argc, char* argv[]){
	//unsigned int i = 12;
	//printf("hex:%04x regular:%d\n", i, i);
	//printBits(i, 8);
/*
	shiftCompare(0x80000000, 2);
	shiftCompare(0xF0000000, 3);
	shiftCompare(0x80008000, 2);
*/
	//unsigned char ch = 0x5c;
	/*
	for(int i = 0; i < 8; i++){
		printf("get Bit(0x%02x, index:%d): %d\n", ch, i, getBit(ch, i));
	}
	printBits(ch, 4);
*/
	/*
	for(int i = 0; i < 8; i++){
			printBits(ch, 4);
			printf("set Bit(0x%02x, index:%d): %02x\n", ch, i, setBit(ch, i));
			printBits(setBit(ch,i), 4);
			printf("clear Bit(0x%02x, index:%d): %02x\n", ch, i, clearBit(ch, i));
			printBits(clearBit(ch,i), 4);
			printf("\n");
		}
	*/
	add(0x0f, 0x2b);
	printf("%d\n",add(0x0f, 0x2b));
	return 0;
}
