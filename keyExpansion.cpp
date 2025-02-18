// import needed libraries
#include "AES.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// function for performing subword
AES subWord(AES k){
	// loops through bytes in word
	for(int i = 0; i < 4; i++){
		// get row index
		unsigned int row = k.word[i];
		row = row&0xF0;
		row = row >> 4;
		
		// get column index
		unsigned int col = k.word[i];
		col = col&0x0F;
		
		// replace bytes in word with byte from stable
		k.word[i] = sTable[row][col];
	}

	return k;
}

// function for performing rotword
AES rotWord(AES k){
	// initialize temp array to make it easier
	unsigned int col[4];
	for(int i = 0; i < 4; i++){
		col[i] = k.word[i];
	}
	
	// rotates the values
	k.word[3] = col[0];
	for(int i = 0; i < 3; i++){
		k.word[i] = col[i+1];
	}
	
	return k;
}

// keyExpansion
int* keyExpansion(AES k, int* ret){
	// creates array to store all of the round keys
	int temp[(1+k.Nr)*k.Nk] = {0};
	
	for(int i = 0; i < (k.Nk); i++){
		temp[i] = stoul(k.key[i],0,16);
	}

	// gets word
	for(int i = k.Nk; i < (k.Nr*k.Nk)+k.Nk; i++){
		// translates words into bytes
		k.word[0] = (temp[i - 1] >> 24)&0xFF;
		k.word[1] = (temp[i - 1] >> 16)&0xFF;
		k.word[2] = (temp[i - 1] >> 8)&0xFF;
		k.word[3] = (temp[i - 1] >> 0)&0xFF;
		
		// need to do operations 
		if((i%k.Nk) == 0){
			
			k = rotWord(k);
			k = subWord(k);
			
			// get needed rcon values
			unsigned int rcon[4];
			for(int x = 0; x < 4; x++){
				rcon[x] = (unsigned int)Rcon[(i/k.Nk) - 1][x];
			}
			
			// xor with rcon with add function
			for(int x = 0; x < 4; x++){
				k.word[x] = ffAdd(k.word[x],rcon[x]);
			}
		}
		// subword for certain values
		else if((k.Nk > 6)&&(i%k.Nk == 4)){
			k = subWord(k);
		}

		// translate word to bytes
		unsigned int val[4];
		val[0] = (temp[i - k.Nk] >> 24)&0xFF;
		val[1] = (temp[i - k.Nk] >> 16)&0xFF;
		val[2] = (temp[i - k.Nk] >> 8)&0xFF;
		val[3] = (temp[i - k.Nk] >> 0)&0xFF;

		// do XOR operation through add function
		for(int x = 0; x < 4; x++){
			k.word[x] = ffAdd(k.word[x], val[x]);
		}
		
		// puts bytes back into word and save
		temp[i] = int((k.word[0]) << 24 | (k.word[1]) << 16 | (k.word[2]) << 8 | (k.word[3]));
			
	}

	// save values to pointer
	for(int x = 0; x < (1+k.Nr)*k.Nk; x++){
		ret[x] = temp[x];
	}
	
	return ret;
}
