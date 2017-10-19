// Developer : Raymond Zhang
// Purpose : UWB CSS 337 Secure Systems, Homework 1 Part 1
// Description : This contains all the necessary methods to accomplish HW1, part 1.
//				Uses int arrays to mimic bytes
//				It requires two inputs: Key, Plaintext. This program has built in S-blocks
//				and will XOR the key with the plaintext, use a word input for the S-block,
//				and the output of the S-block is the ciphertext. 

#include "Cipher.h"
#include <iostream> 
using namespace std;

int main () {
 
	// start of part 1
	// display information
	Cipher partOne;
	cout << "******************** Displaying Initial Information ********************" << endl;
	partOne.allocateBoxes();
	partOne.allocateKeys("plaintext", 0,"1001010001100110");
	partOne.allocateKeys("plaintext",1,"0010100111000010");
	partOne.allocateKeys("plaintext",2,"0101110011100010");
	partOne.allocateKeys("plaintext",3,"1001110000100111");
	partOne.allocateKeys("key",0,"1010001000111010");
	partOne.printKeys("printAll", 4);
	cout << "********************  Done Displaying Information   ********************" << endl;
	// start encrypting with key
	cout << "KEY XOR A1-A4 (Plaintext) " << endl;
	partOne.encrypt();
	partOne.sboxTable(4);
	partOne.printKeys("",4);
	// end of part 1
	cout << "********************  Part 1 end, Part 2 start   ********************" << endl;

	//start part 2 
	Cipher partTwo;
	partTwo.allocateBoxes();
	partTwo.allocateKeys("plaintext",0,"1001010001100110");
	partTwo.allocateKeys("plaintext",1,"0010100111000010");
	partTwo.allocateKeys("plaintext",2,"0101110011100010");
	partTwo.allocateKeys("plaintext",3,"1001110000100111");
	partTwo.allocateKeys("plaintext",4,"1011110111011111");
	partTwo.allocateKeys("plaintext",5,"0001110100010011");
	partTwo.allocateKeys("plaintext",6,"1110000111000011");
	partTwo.allocateKeys("plaintext",7,"0011111000000010");
	partTwo.allocateKeys("plaintext",8,"0101001111011011");
	partTwo.allocateKeys("plaintext",9,"1100001001110100");
	partTwo.allocateKeys("key",0,"1010001000111010");
	partTwo.printKeys("printAll", 10);
	
	partTwo.encryptTwo();
	partTwo.printKeys("", 10);

	

	
}