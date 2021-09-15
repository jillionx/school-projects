/*Author: Jill Russell
CIS 111 - Project 3
Affine Cipher Program
*/


//INCLUDES AND DEFINES
#pragma warning (disable:4996)
#pragma warning (disable:6031)

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>			//for system() function/directory command

#ifndef __TRUE_FALSE__
#define __TRUE_FALSE__
#define TRUE 1
#define FALSE 0
#endif

#define NO_INVERSE -1
#define ERROR -2

#define A 1
#define B 1
#define ALPHABET_SIZE 26

#define BUFFER_SIZE 10000
#define NAME_SIZE
#define ASCII_OFFSET 97
#define ASCII_UPPER_LOWER_OFFSET 32

#define INPUT_SELECT		1
#define OUTPUT_SELECT		2
#define KEY_SELECT			3
#define ENCRYPT_SELECT		4
#define DECRYPT_SELECT		5
#define DIRECTORY_SELECT	6
#define EXIT_SELECT			7

// PROTOTYPES
int ReadStringFromFile(char*, char*, int&);
int WriteStringToFile(char*, char*, int&);
int CleanString(char*);
int EncryptString(char*, int, int, int);
int DecryptString(char*, int, int, int);
int ModularInverse(int, int);
int IsPrime(int);
int CoprimeTest(int, int);

//MAIN
int main() {
	//set variables that may be rewritten throughout program
	int programRunning = TRUE;
	int a = A;
	int b = B;
	char INPUT_FILE[] = "input.txt";
	char OUTPUT_FILE[] = "output.txt";

	while (programRunning == TRUE) {
		//set variables that need to be reset through each step
		char buffer[BUFFER_SIZE] = "";
		int readSuccess = FALSE;
		int writeSuccess = FALSE;
		int optionSelect = FALSE;
		//calculate inverse for display
		int inverse = ModularInverse(a, ALPHABET_SIZE);

		//Display current values
		printf("Affine Cipher Program\n");
		printf("---------------------\n");
		printf("The current input file is : %s\n", INPUT_FILE);
		printf("The current output file is: %s\n", OUTPUT_FILE);
		printf("Affine Cipher - e(x) = (Ax + B)(mod 26)\n");
		printf("A = %d A^(-1) = %d\n", a, inverse);
		printf("B = %d\n", b);
		printf("---------------------\n");
		//Display options to user
		printf("Please select an option:\n");
		printf("1.) Select input file name\n");
		printf("2.) Select output file name\n");
		printf("3.) Select affine cipher key\n");
		printf("4.) Encrypt input file\n");
		printf("5.) Decrypt input file\n");
		printf("6.) Get directory listing\n");
		printf("7.) Exit\n");
		printf(":");
		//Prompt for option and verify selection
		scanf("%d", &optionSelect);

		if (optionSelect == INPUT_SELECT) {
			printf("Input File Name:");
			scanf("%s", INPUT_FILE);
			printf("\nCommand Executed...Press Any Key to Continue\n\n");
		}
		if (optionSelect == OUTPUT_SELECT) {
			printf("Output File Name:");
			scanf("%s", OUTPUT_FILE);
			printf("\nCommand Executed...Press Any Key to Continue\n\n");
		}
		if (optionSelect == KEY_SELECT) {
			printf("Enter a value for A: ");
			scanf("%d", &a);
			printf("Enter a value for B: ");
			scanf("%d", &b);

			int inverseCode = ModularInverse(a, ALPHABET_SIZE);
			while (inverseCode == NO_INVERSE || inverseCode == ERROR) {
				printf("You cannot encrypt with key (%d, %d) on a (mod %d) ring. Please select a new key.\n", a, b, ALPHABET_SIZE);
				printf("Enter a value for A: ");
				scanf("%d", &a);
				printf("Enter a value for B: ");
				scanf("%d", &b);
				inverseCode = ModularInverse(a, ALPHABET_SIZE);
			}
				printf("\nCommand Executed...Press Any Key to Continue\n\n");
		}
		if (optionSelect == ENCRYPT_SELECT) {
			ReadStringFromFile(INPUT_FILE, buffer, readSuccess);
			if (readSuccess == TRUE) {
				printf("Plain Text : ");
				puts(buffer);
				CleanString(buffer);
				printf("Sanitized Plain Text : ");
				puts(buffer);
				EncryptString(buffer, a, b, ALPHABET_SIZE);
				WriteStringToFile(OUTPUT_FILE, buffer, writeSuccess);
				if (writeSuccess == TRUE) {
					printf("Cipher Text : ");
					puts(buffer);
					printf("\nCommand Executed...Press Any Key to Continue\n\n");
				}
			}
		}

		if (optionSelect == DECRYPT_SELECT) {
			ReadStringFromFile(INPUT_FILE, buffer, readSuccess);

			if (readSuccess == TRUE) {
				printf("Cipher Text : ");
				puts(buffer);
				DecryptString(buffer, a, b, ALPHABET_SIZE);
				WriteStringToFile(OUTPUT_FILE, buffer, writeSuccess);
				if (writeSuccess == TRUE) {
					printf("Plain Text : ");
					puts(buffer);
					printf("\nCommand Executed...Press Any Key to Continue\n\n");
				}
			}
		}
		if (optionSelect == DIRECTORY_SELECT) {
			system("dir /p");
			printf("\nCommand Executed...Press Any Key to Continue\n\n");
		}
		if (optionSelect == EXIT_SELECT) {
			return 0;
		}
		_getch();
	}
}

//FUNCTIONS
int ReadStringFromFile(char* INPUT_FILE, char* buffer, int& readSuccess) {
	FILE* inputFile = NULL;
	char charHolder = ' ';

	// open the file (read)
	inputFile = fopen(INPUT_FILE, "r");

	// confirm the file opened
	if (inputFile == NULL) {
		printf("The file was not successfully read. Please check input file name against the file directory and try again.\n");
		readSuccess = FALSE;
		return readSuccess;
	}
	else {
		while (fgets(buffer, BUFFER_SIZE, inputFile) != NULL);

		//close file
		fclose(inputFile);
		readSuccess = TRUE;
		return readSuccess;
	}
}

int WriteStringToFile(char* OUTPUT_FILE, char* buffer, int& writeSuccess) {
	FILE* outputFile = NULL;

	// open file (write)
	outputFile = fopen(OUTPUT_FILE, "w");

	// confirm that file opened
	if (outputFile == NULL) {
		printf("The file was not successfully written.\n");
		writeSuccess = FALSE;
		return writeSuccess;
	}

	else {
		// put data into file
		fprintf(outputFile, "%s", buffer);

		// close file
		fclose(outputFile);
		writeSuccess = TRUE;
		return writeSuccess;
	}
}

int CleanString(char* buffer) {
	// create clean buffer
	char cleanBuffer[BUFFER_SIZE];

	// point to original buffer
	char* originalIterator = buffer;

	// pointer to clean buffer
	char* cleanIterator = cleanBuffer;

	// clean string one character at a time
	while (*originalIterator != '\0') {
		// copy lowercase
		if (*originalIterator >= 'a' && *originalIterator <= 'z') {
			*cleanIterator = *originalIterator;
			cleanIterator++;
		}

		// convert uppercase to lowercase
		else if (*originalIterator >= 'A' && *originalIterator <= 'Z') {
			*cleanIterator = *originalIterator + 32;
			cleanIterator++;
		}

		// next character
		originalIterator++;
	}

	// null terminate clean buffer
	*cleanIterator = '\0';

	// copy into buffer
	strcpy(buffer, cleanBuffer);

	return 0;
}

int EncryptString(char* encryptMe, int a, int b, int n) {
	//YOUR IMPLEMENTATION GOES HERE
	int i = 0;
	int PTCodes[BUFFER_SIZE];

	// check to make sure we are safe for encryption
	int inverseCode = ModularInverse(a, n);
	if (inverseCode == -1 || inverseCode == -2) {
		printf("You cannot encrypt with key (%d, %d) on a (mod %d) ring.\n", a, b, n);
		return FALSE;
	}

	// copy the ASCII array codes into the PTCodes array
	i = 0;
	while (encryptMe[i] != '\0') {
		PTCodes[i] = encryptMe[i];
		i++;
	}
	PTCodes[i] = -1;

	// reduce character ASCII codes to PT codes
	i = 0;
	while (PTCodes[i] != -1) {
		PTCodes[i] -= ASCII_OFFSET;
		i++;
	}

	// encrypt PT codes
	i = 0;
	while (PTCodes[i] != -1) {
		PTCodes[i] = (PTCodes[i] * a + b) % n;
		i++;
	}

	// revert PT codes to ASCII codes
	i = 0;
	while (PTCodes[i] != -1) {
		PTCodes[i] += ASCII_OFFSET;
		i++;
	}

	// copy the PT codes array back into the ASCII codes array
	i = 0;
	while (PTCodes[i] != -1) {
		encryptMe[i] = PTCodes[i];
		i++;
	}
	encryptMe[i] = '\0';

	// return success
	return TRUE;
}

int DecryptString(char* decryptMe, int a, int b, int n) {
	int i = 0;
	int PTCodes[BUFFER_SIZE];

	// check to make sure we are safe for decryption
	int inverseCode = ModularInverse(a, n);
	if (inverseCode == -1 || inverseCode == -2) {
		printf("Decryption could not be completed.\n");
		return FALSE;
	}

	// copy the ASCII array codes into the PTCodes array
	i = 0;
	while (decryptMe[i] != '\0') {
		PTCodes[i] = decryptMe[i];
		i++;
	}
	PTCodes[i] = -1;

	// reduce character ASCII codes to PT codes
	i = 0;
	while (PTCodes[i] != -1) {
		PTCodes[i] -= ASCII_OFFSET;
		i++;
	}

	// decrypt PT codes
	i = 0;
	while (PTCodes[i] != -1) {
		PTCodes[i] = inverseCode * (PTCodes[i] - b + n) % n;
		i++;
	}

	// revert PT codes to ASCII codes
	i = 0;
	while (PTCodes[i] != -1) {
		PTCodes[i] += ASCII_OFFSET;
		i++;
	}

	// copy the PT codes array back into the ASCII codes array
	i = 0;
	while (PTCodes[i] != -1) {
		decryptMe[i] = PTCodes[i];
		i++;
	}
	decryptMe[i] = '\0';

	// return success
	return TRUE;
}

int ModularInverse(int target, int mod) {
	int inverse = 1;

	// determine if the target has an inverse in this
	// particular modular system
	if (CoprimeTest(target, mod) == FALSE)
		return NO_INVERSE;

	// if the target has an inverse, find it!
	for (inverse = 1; inverse <= mod; inverse++) {
		if ((target * inverse) % mod == 1) {
			return inverse;
		}
	}

	// if we got through this loop and didn't find an inverse
	// something is not working properly
	return ERROR;

	return 0;
}

int IsPrime(int amIPrime) {
	int i = 0;
	int isPrime = TRUE;

	// check for border cases
	if (amIPrime <= 1) {
		isPrime = FALSE;
	}

	// force check the number for primality
	for (i = 2; i < amIPrime; i++) {
		if (amIPrime % i == 0)
			isPrime = FALSE;
	}

	return isPrime;
}

int CoprimeTest(int numOne, int numTwo) {
	int i = 0;
	int areCoprime = TRUE;
	int larger = 0;
	int smaller = 0;

	// determine that larger of the two numbers
	if (numOne >= numTwo) {
		larger = numOne;
		smaller = numTwo;
	}
	else {
		larger = numTwo;
		smaller = numOne;
	}

	for (i = 1; i <= larger; i++) {
		// find a prime factor for numOne
		if (larger % i == 0 && IsPrime(i))
			// determine if numTwo is divisible by the candidate prime
			if (smaller % i == 0)
				areCoprime = FALSE;
	}

	// return the result
	return areCoprime;
}