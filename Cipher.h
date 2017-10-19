// Developer : Raymond Zhang
// Purpose : UWB CSS 337 Secure Systems, Homework 1 Part 1
// Description : This contains all the necessary methods to accomplish HW1, part 1.
//				Uses int arrays to mimic bytes
//				It requires two inputs: Key, Plaintext. This program has built in S-blocks
//				and will XOR the key with the plaintext, use a word input for the S-block,
//				and the output of the S-block is the ciphertext. 

#ifndef CIPHER
#define CIPHER
#include <string>
using namespace std;

class Cipher {

public:
	Cipher();
	void allocateKeys(string form, int row, string key);
	void allocateBoxes();	
	void printKeys(string, int);
	void encrypt();
	void encryptTwo();
	void sboxTable(int);

private:

	// plaintext, ciphertext, key, and two s-boxes
	int plaintext[10][16];
	int cipherText[10][16];
	int encryptKey[16];
	int sboxOne[4][4];
	int sboxTwo[4][4];

	// used to measure percentage changed on part 2
	int MAXBITS;
	double changedBit;
};
#endif