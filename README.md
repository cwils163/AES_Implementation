# AES Project
Name: Constance Wilson
Goal: Develop code that will perform AES encryption and decryption on hard coded values.

## Contents
- `appendix_c.txt`: text file containing example output that can be used to check the results of the code
- `AES.h`: header file that connects all of the .cpp files and initializes shared data structures and functions
- `BaseOps.cpp`: C++ file that contains mathematical and print functions that are commonly used throughout the other files
- `cipher.cpp`: C++ file that contains the code required to perform AES encryption
- `invCipher.cpp`: C++ file that contains the code required to perform AES decryption
- `keyExpansion.cpp`: C++ file that performs key expansion, a process needed before encryption can occur
- `main.cpp`: C++ file that uses functions from the other files to perform AES encryption/decrpyion and print the results

## How to Compile Code
In order to run this code, start by downloading or cloning this repository. Navigate to the file location and use one of the following commands:
- `make`: compiles the code
- `./AES`: runs the code
- `make test`: compares output of the code to the example output given in `appendex_c.txt`
- `make clean`: removes files made by `make` to compile the code
