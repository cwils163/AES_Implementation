// import needed libraris
#include "AES.h"
#include <iostream>
#include <iomanip>

// function for inverse subbytes operation
AES invSubBytes(AES val){
	// loops through state
	for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
			// gets row value
                        unsigned int row = val.state[i][j];
                        row = row&0xF0;
                        row = row >> 4;

			// gets column value
                        unsigned int col = val.state[i][j];
                        col = col&0x0F;

			// saves value from inverse stable
                        val.state[i][j] = invSTable[row][col];
                }
        }
        return val;
}

// function for inverse shiftrows operation
AES invShiftRows(AES val){
	// initializes temp array for easier shift
	unsigned int og[4];
        unsigned int n[4];

	// loops through 3 rows that need to be shifted
        for(int i = 1; i < 4; i++){
		// sets up temp values
                for(int k = 0; k < 4; k++){
                        og[k] = val.state[k][i];
                        n[k] = val.state[k][i];
                }

		// loops through rows
                for(int x = 0; x < i; x++){
			// shifts bytes over
                        n[0] = og[3];
                        for(int y = 1; y < 4; y++){
                                n[y] = og[y-1];
                        }

			// saves new row order
                        for(int j = 0; j < 4; j++){
                                og[j] = n[j];
                        }
                }

		// saves row to state
                for(int k = 0; k < 4; k++){
                        val.state[k][i] = n[k];
                }
        }
        return val;	
}

// function for inverse mixcolumns operation
AES invMixColumns(AES val){
	// initializes needed data
	unsigned int sum = 0;
        unsigned int prod;
        unsigned int tmp[4];

	// loops through state
        for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                        // calculates value
			for(int k = 0; k < 4; k++){
                        	prod = ffMultiply(invRGF[j][k], val.state[i][k]);
                        	sum = ffAdd(sum, prod);
                        }
                        
			// saves new value
                        tmp[j] = sum;
                        
                        sum = 0;
                }

		// puts new values into the state
                for(int j = 0; j < 4; j++){
                        val.state[i][j] = tmp[j];
                }
        }

        return val;
}

// funciton for decryption
AES invCipher(AES val, int* w){
	// prints out inputted state
	cout << "round[ 0].iinput    ";
	printState(val);
	
	// get and print round key
	unsigned int rk[4];
	cout << "round[ 0].ik_sch    ";
        for(int i = 0; i < 4; i++){
                rk[i] = w[(val.Nr*4) + i];
		cout << hex << nouppercase << setw(8) << setfill('0') << rk[i] << dec << setfill(' ');
        }
	cout << endl;

	// calls addroundkey
        val = AddRoundKey(val, rk);
	
	// goes through all rows but final
        for(int i = 1; i < val.Nr; i++){
		// prints state at the start of the round
                cout << "round[" << setw(2) << i << "].istart    ";
		printState(val);

		// get and print state after invshiftrows
		val = invShiftRows(val);
		cout << "round[" << setw(2) << i << "].is_row    ";
		printState(val);

		// get and print state after invsubbytes
                val = invSubBytes(val);
		cout << "round[" << setw(2) << i << "].is_box    ";
		printState(val);

		// get and print key round
		cout << "round[" <<  setw(2) << i << "].ik_sch    ";
                for(int j = 0; j < 4; j++){
                        rk[j] = w[((val.Nr-i)*4) + j];
			cout << hex << nouppercase << setw(8) << setfill('0') << rk[j] << dec << setfill(' ');
                }
		cout << endl;

		// get and print state after addroundkey
                val = AddRoundKey(val, rk);
		cout << "round[" << setw(2) << i << "].ik_add    ";
		printState(val);

		// perform inverse mixcolumns
		val = invMixColumns(val);
        }
	
	// print out starting state of final round
	cout << "round[" << setw(2) << val.Nr << "].istart    ";
	printState(val);

	// get and print out state after final inverse shiftrows
        val = invShiftRows(val);
	cout << "round[" << setw(2) << val.Nr << "].is_row    ";
	printState(val);

	// get and print out state after final inverse subbytes
        val = invSubBytes(val);
	cout << "round[" << setw(2) << val.Nr << "].is_box    ";
	printState(val);

	// get and print final round key
	cout << "round[" << setw(2) << val.Nr << "].ik_sch    ";
        for(int j = 0; j < 4; j++){
                rk[j] = w[0 + j];
		cout << hex << nouppercase << setw(8) << setfill('0') << rk[j] << dec << setfill(' ');
        }
	cout << endl;

	// perform final addroundkey
        val = AddRoundKey(val, rk);

	// print final state
	cout << "round[" << setw(2) << val.Nr << "].ioutput   ";
	printState(val);
	
        return val;
}
