// imports needed libraries and AES header
#include "AES.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
	AES vals; // initialize AES struct

	// plaintext
	unsigned char pt[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
	
	// array to hold words that make up the 128 bit key
	string k1[] = {"00010203", "04050607", "08090a0b", "0c0d0e0f"};
	
	// array to hold words that make up the 192 bit key
	string k2[] = {"00010203","04050607","08090a0b","0c0d0e0f","10111213","14151617"};
	
	// array to hold words that make up the 256 bit key
	string k3[] = {"00010203","04050607","08090a0b","0c0d0e0f","10111213","14151617","18191a1b","1c1d1e1f"};

	// stores plaintext into AES struct
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			vals.state[j][i] = (int)pt[i + (4*j)]; 
		}
	}
	
	cout << "C.1   AES-128 (Nk=4, Nr=10)" << endl << endl;
	cout << "PLAINTEXT:          ";
	printState(vals);
	
	// stores needed values into AES struct
	vals.Nk = 4;
	vals.Nr = 10;
	vals.key = k1;

	cout << "KEY:                ";
	printKeys(vals);
	cout << endl << "CIPHER (ENCRYPT):" << endl;

	// creates pointer to hold cipher key and all round keys
	int *w = new int[(1+vals.Nr)*vals.Nk]{};
	// runs key expansion
	w = keyExpansion(vals, w);
	
	// runs encryption algorithm
	vals = Cipher(vals, w);

	cout << "INVERSE CIPHER (DECRYPT):" << endl;
	vals = invCipher(vals, w); // runs decryption algorithm
	cout << endl;
	delete w; // frees up memory from pointer
	
	// resets plaintext held in AES struct
	for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                        vals.state[j][i] = (int)pt[i + (4*j)];
                }
        }

	cout << "C.2   AES-192 (Nk=6, Nr=12)" << endl << endl;
	cout << "PLAINTEXT:          ";
	printState(vals); // prints plaintext

	// saves needed values to AES struct
	vals.Nk = 6;
	vals.Nr = 12;
	vals.key = k2;
	
	cout << "KEY:                ";
	printKeys(vals); // prints key
	cout << endl << "CIPHER (ENCRYPT):" << endl;

	// gets cipher key and round keys
        int *w2 = new int[(1+vals.Nr)*vals.Nk]{};
        w2 = keyExpansion(vals, w2);
        
        vals = Cipher(vals, w2); // run encryption
	
	cout << "INVERSE CIPHER (DECRYPT):" << endl;
        vals = invCipher(vals, w2); // run decryption
	cout << endl;
        
	delete w2; // free memory from pointer

	// reset plaintext in AES struct
	for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                        vals.state[j][i] = (int)pt[i + (4*j)];
                }
        }

	cout << "C.3   AES-256 (Nk=8, Nr=14)" << endl << endl;
	cout << "PLAINTEXT:          ";
	printState(vals); // prints plaintext

	// sets needed values in AES struct
	vals.Nk = 8;
        vals.Nr = 14;
        vals.key = k3;
	
	cout << "KEY:                ";
	printKeys(vals); // prints key
	cout << endl << "CIPHER (ENCRYPT):" << endl;

	// gets cipher key and round keys
        int *w3 = new int[(1+vals.Nr)*vals.Nk]{};
        w3 = keyExpansion(vals, w3);
        
	// runs encryption
        vals = Cipher(vals, w3);
        
	// runs decryption
	cout << "INVERSE CIPHER (DECRYPT):" << endl;
        vals = invCipher(vals, w3);
        
        delete w3; // free memory from pointer
	
	return 0;
}
