// imports needed libraries
#include "AES.h"
#include <iostream>
#include <iomanip>

// function for performing AddRoundKey function
AES AddRoundKey(AES val, unsigned int rk[4]){
	for(int i = 0; i < 4; i++){
		unsigned int col[4];

		// gets bytes from the word and stores them in col[]
		col[0] = (rk[i] >> 24)&0xFF;
		col[1] = (rk[i] >> 16)&0xFF;
		col[2] = (rk[i] >> 8)&0xFF;
		col[3] = (rk[i] >> 0)&0xFF;

		// saves result
		for(int j = 0; j < 4; j++){
			val.state[i][j] = ffAdd(val.state[i][j], col[j]);
		}
		
	}
	return val;
}

// function for performing subBytes function
AES subBytes(AES val){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			// gets row value
			unsigned int row = val.state[i][j];
			row = row&0xF0;
			row = row >> 4;

			// gets column value
			unsigned int col = val.state[i][j];
			col = col&0x0F;

			// gets value from the stable
			val.state[i][j] = sTable[row][col];
		}
	}
	return val;	
}

// function for performing shiftRows function
AES shiftRows(AES val){
	// initializes two temporary arrays to make shifting easier
	unsigned int og[4];
	unsigned int n[4];

	// goes through the 3 rows that need to be shifted
	for(int i = 1; i < 4; i++){
		// sets up temp arrays
		for(int k = 0; k < 4; k++){
			og[k] = val.state[k][i];
			n[k] = val.state[k][i];
		}
		
		// goes through values in column
		for(int x = 0; x < i; x++){
			// shifts row
			n[3] = og[0];
			for(int y = 0; y < 3; y++){
				n[y] = og[y+1];
			}
			
			// saves value
			for(int j = 0; j < 4; j++){
				og[j] = n[j];
			}
		}

		// saves value to state
		for(int k = 0; k < 4; k++){
			val.state[k][i] = n[k];
		}
	}
	return val;
}

// function for mixColumns function
AES mixColumns(AES val){
	// initialize needed values
	unsigned int sum = 0;
	unsigned int prod;
	unsigned int tmp[4];

	// loops through array
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			// calculates new value
			for(int k = 0; k < 4; k++){
				prod = ffMultiply(RGF[j][k], val.state[i][k]);
				sum = ffAdd(sum, prod);
			}
			
			// saves new value
			tmp[j] = sum;
			
			sum = 0;
		}

		// saves new values to state
		for(int j = 0; j < 4; j++){
			val.state[i][j] = tmp[j];
		}
	}
	return val;
}

AES Cipher(AES val, int* w){
	cout << "round[ 0].input     ";
	printState(val); // print input
	
	cout << "round[ 0].k_sch     ";
	// gets round key
	unsigned int rk[4];
	for(int i = 0; i < 4; i++){ // sets and prints round key by word
		rk[i] = w[i];
		cout << hex << nouppercase << setw(8) << setfill('0') << rk[i] << dec << setfill(' ');
	}
	cout << endl;

	// adds round key
	val = AddRoundKey(val, rk);
	
	// goes through all but final rounds
	for(int i = 1; i < val.Nr; i++){ 
		cout << "round[" << setw(2) << i << "].start     ";
		printState(val); // prints starting state

		// get and print state after subbytes
		cout << "round[" << setw(2) << i << "].s_box     ";
		val = subBytes(val);
		printState(val);

		// get and print state after shiftrows
		cout << "round[" << setw(2) << i << "].s_row     ";
		val = shiftRows(val);
		printState(val);

		// get and print state after mixcolumns
		cout << "round[" << setw(2) << i << "].m_col     ";
		val = mixColumns(val);
		printState(val);

		// get and print round key
		cout << "round[" << setw(2) << i << "].k_sch     ";
		for(int j = 0; j < 4; j++){
			rk[j] = w[i*4 + j];
			cout << hex << nouppercase << setw(8) << setfill('0') << rk[j] << dec << setfill(' ');
		}
		cout << endl;

		// does roundkey operation
		val = AddRoundKey(val, rk);
	}

	// gets starting state for final round
	cout << "round[" << setw(2) << val.Nr << "].start     ";
	printState(val);

	// get and print state after subbytes
	cout << "round[" << setw(2) << val.Nr << "].s_box     ";
	val = subBytes(val);
	printState(val);

	// get and print state after shiftrows
	cout << "round[" << setw(2) << val.Nr << "].s_row     ";
	val = shiftRows(val);
	printState(val);
	
	// get and print final round key
	cout << "round[" << setw(2) << val.Nr << "].k_sch     ";
	for(int j = 0; j < 4; j++){
		rk[j] = w[(val.Nr*4) + j];
		cout << hex << nouppercase << setw(8) << setfill('0') << rk[j] << dec << setfill(' ');
	}
	cout << endl;

	// perform addroundkey operation
	val = AddRoundKey(val, rk);

	// print final state	
	cout << "round[" << setw(2) << val.Nr << "].output    ";
	printState(val);
	cout << endl;

	return val;
}
