#ifndef VOLSORT_H
#define VOLSORT_H

#include <string>

using namespace std;

// define needed matrices
extern unsigned char Rcon[][10];
extern unsigned char RGF[][4];
extern unsigned char invRGF[][4];
extern unsigned char sTable[][16];
extern unsigned char invSTable[][16];

//struct to save needed values
struct AES{
	int Nk;
	int Nr;
	unsigned int state[4][4];
	string* key;
	unsigned int word[4];
};

// initalize needed arrays
void printState(AES s);
void printKeys(AES s);
int ffAdd(int num1, int num2);
int xtimes(int num);
int ffMultiply(int num1, int num2);
int* keyExpansion(AES k, int* result);
AES rotWord(AES k, int col[], int ind);
AES Cipher(AES val, int* w);
AES AddRoundKey(AES val, unsigned int rk[4]);
AES subBytes(AES val);
AES shiftRows(AES val);
AES mixColumns(AES val);
AES invCipher(AES val, int* w);
AES invShiftRows(AES val);
AES invSubBytes(AES val);

#endif
