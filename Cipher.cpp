// Developer : Raymond Zhang
// Purpose : UWB CSS 337 Secure Systems, Homework 1 Part 1
// Description : This contains all the necessary methods to accomplish HW1, part 1.
//				Uses int arrays to mimic bytes
//				It requires two inputs: Key, Plaintext. This program has built in S-blocks
//				and will XOR the key with the plaintext, use a word input for the S-block,
//				and the output of the S-block is the ciphertext. 

#include "Cipher.h"
#include <iostream>

// constructor responsible for 0 initialize all the arrays
Cipher :: Cipher () {
	for (int row = 0; row < 10; row++) {
		for (int col = 0; col < 16; col++) {
			plaintext[row][col] = 0;
			cipherText[row][col] = 0;
			encryptKey[col] = 0;
		}
	}
		
	for (int row; row < 4; row++) {
		for (int col; col < 4; col ++ ) {
			sboxOne[row][col] = 0;
			sboxTwo[row][col] = 0;
		}
	}

	MAXBITS = 16;
	changedBit = 0;
}

// takes key input from main. this method sets the value for plaintext and key
void Cipher :: allocateKeys (string form, int row, string key) {
	for (int i = 0 ; i < 16; i++ ) {
		// is form plaintext? if not its a key
		if (form == "plaintext") {
			if (key[i] == '0') {
				plaintext[row][i] = 0;
			} else {
				plaintext[row][i] = 1;
			}
		} else {
			if (key[i] == '0') {
				encryptKey[i] = 0;
			} else {
				encryptKey[i] = 1;
			}
		}
	}
}

// Any value changes to S-block will be made here
void Cipher :: allocateBoxes () {
	// box 1 start
	sboxOne[0][0] = 15;
	sboxOne[0][1] = 10;
	sboxOne[0][2] = 2;
	sboxOne[0][3] = 5;

	sboxOne[1][0] = 8;
	sboxOne[1][1] = 4;
	sboxOne[1][2] = 11;
	sboxOne[1][3] = 6;

	sboxOne[2][0] = 1;
	sboxOne[2][1] = 0;
	sboxOne[2][2] = 14;
	sboxOne[2][3] = 7;

	sboxOne[3][0] = 9;
	sboxOne[3][1] = 3;
	sboxOne[3][2] = 12;
	sboxOne[3][3] = 13;

	// box 1 end, box 2 start
	sboxTwo[0][0] = 4;
	sboxTwo[0][1] = 0;
	sboxTwo[0][2] = 15;
	sboxTwo[0][3] = 10;

	sboxTwo[1][0] = 8;
	sboxTwo[1][1] = 9;
	sboxTwo[1][2] = 7;
	sboxTwo[1][3] = 13;

	sboxTwo[2][0] = 5;
	sboxTwo[2][1] = 1;
	sboxTwo[2][2] = 6;
	sboxTwo[2][3] = 11;

	sboxTwo[3][0] = 2;
	sboxTwo[3][1] = 3;
	sboxTwo[3][2] = 14;
	sboxTwo[3][3] = 12;
	// box 2 end

	// print values of Sbox 1 & 2
	cout << "\nS-Box Table 1: " << endl;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			cout << sboxOne[row][col] << " ";
		}
		cout << endl;
	}

	cout << "\nS-Box Table 2: " << endl;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			cout << sboxTwo[row][col] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// this is where the plaintext XOR key
void Cipher :: encrypt() {
	// K XOR A1-4
	for (int row = 0; row < 4; row++) {

		for (int col = 0; col < 16; col++) {
			// 0 0, ciphertext goes to 0		
			// 0 1, ciphertext goes to 1
			// 1 0, ciphertext goes to 1
			// 1 1, ciphertext goes to 0

			if ( (plaintext[row][col] == encryptKey[col]) && (encryptKey[col] == 0) ) {
				cipherText[row][col] = 0;
			} else if ( (plaintext[row][col] == encryptKey[col]) && (encryptKey[col] == 1) ) {
				cipherText[row][col] = 0;
			} else if ( (plaintext[row][col] != encryptKey[col]) && (encryptKey[col] == 0) ) {
				cipherText[row][col] = 1;
			} else if ( (plaintext[row][col] != encryptKey[col]) && (encryptKey[col] == 1) ) {
				cipherText[row][col] = 1;
			} 
		}
	}
	cout << endl;	
}

// this is used after encryption. this maps (key XOR plaintext) to sbox
void Cipher :: sboxTable (int max) {
	// S1(A2 XOR K1)
	// S2(A4 XOR K3)
	// S1(A1 XOR K2)
	// S2(A3 XOR K4)
	
	//cout << "Find Value (Coordinate of Sblock)" << endl;
	int xAxis;
	int yAxis;

	int swapBox = 0;

	// traverse a row at a time
	for (int row = 0; row < max; row ++) {
		// operate a word at a time
		for (int col = 0; col < 16; col = col + 4) {
			if (cipherText[row][col] == 0 && cipherText[row][col+1] == 0) {
				xAxis = 0;
				//cout << "x:00 "; 
			} else if ( cipherText[row][col] == 0 && cipherText[row][col+1] == 1 ) {
				xAxis = 1;
				//cout << "x:01 "; 
			} else if ( cipherText[row][col] == 1 && cipherText[row][col+1] == 0) {
				xAxis = 2;
				//cout << "x:10 "; 
			} else {
				xAxis = 3;
				//cout << "x:11 "; 
			}

			if (cipherText[row][col+2] == 0 && cipherText[row][col+3] == 0) {
				yAxis = 0;
			//	cout << "y:00 "; 
			} else if ( cipherText[row][col+2] == 0 && cipherText[row][col+3] == 1 ) {
				yAxis = 1;
				//cout << "y:01 "; 
			} else if ( cipherText[row][col+2] == 1 && cipherText[row][col+3] == 0 ) {
				yAxis = 2;
				//cout << "y:10 "; 
			} else {
				//cout << "y:11 "; 
				yAxis = 3;
			}

			int value = 0;
			if (swapBox % 2 == 0) {
				value = sboxOne[yAxis][xAxis];
			} else {
				value = sboxTwo[yAxis][xAxis];
			}
			//cout << " value: " << value << endl;
			if (value >= 8) {
				value = value - 8;
				cipherText[row][col] = 1;
			} else {
				cipherText[row][col] = 0;
			}

			if (value >= 4) {
				value = value - 4;
				cipherText[row][col+1] = 1;
			} else {
				cipherText[row][col+1] = 0;
			}

			if (value >= 2) {
				value = value - 2;
				cipherText[row][col+2] = 1;
			} else {
				cipherText[row][col+2] = 0;
			}

			if (value == 1) {
				cipherText[row][col+3] = 1;
			} else {
				cipherText[row][col+3] = 0;
			}
		}
		swapBox++;
	//	cout << endl;
	}
		//cout << "Convert Value (S-block output) to Ciphertext" << endl;
}

// displays all plaintext, ciphertext, and key
void Cipher :: printKeys(string all, int max) {
	// prints all keys if user says "printAll", else just ciphertext
	if (all == "printAll") {
		cout << "Plaintext: " << endl;
		for (int row = 0; row < max; row++) {
			for (int col = 0; col < 16; col++) {
				cout << plaintext[row][col];
			}
			cout << endl;
		}	
		cout << endl;	
		cout << "Key: " << endl;
		for (int i = 0; i < 16; i++) {
			cout << encryptKey[i];
		}
		cout << endl << endl;
	}

	// used to compare before & after without having to print other keys
	cout << "Ciphertext: " << endl;
	for (int row = 0; row < max; row++) {
		for (int col = 0; col < 16; col++) {
			cout << cipherText[row][col];
		}
		cout << endl;;
	}		
	cout << endl;
}

void Cipher :: encryptTwo() {

	int copy[10][16];		
	double total = 0;
	int numberOfOperations = 0;
	double numberOfBitsChanged = 0;
	for (int row = 0; row < 10; row++) {	

		for (int iterate = 0; iterate < 16; iterate++ ) {
			numberOfBitsChanged = 0;
			// copy the plaintext every comparison
			for (int col = 0; col < 16; col++) {
				copy[row][col] = plaintext[row][col];
			}	

			// change 1 bit in copy
			if ( plaintext[row][iterate] == 1) {
				copy[row][iterate] = 0;
			} else {
				copy[row][iterate] = 1;
			}

			// check results for encryption 
			for (int i = 0; i < 16; i++ ) {

				// compare copy to key
				if ( (copy[row][i] == encryptKey[i]) && (encryptKey[i] == 0) ) {
					cipherText[row][i] = 0;
				} else if ( (copy[row][i] == encryptKey[i]) && (encryptKey[i] == 1) ) {
					cipherText[row][i] = 0;
				} else if ( (copy[row][i] != encryptKey[i]) && (encryptKey[i] == 0) ) {
					cipherText[row][i] = 1;
				} else if ( (copy[row][i] != encryptKey[i]) && (encryptKey[i] == 1) ) {
					cipherText[row][i] = 1;
				} 

			}

			sboxTable(row+1);

			for (int i = 0; i < 16; i++) {
				if (plaintext[row][i] != cipherText[row][i]) {
					numberOfBitsChanged++;
				}
			}
			total = total + (numberOfBitsChanged/16 * 100);
			//cout << numberOfBitsChanged / 16 << " ";
			numberOfOperations++;
		}
		//cout << endl;
		
	}	
	cout << "Average of Avalanche Effect: " << total / numberOfOperations;
	cout << endl;
	
}