#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to convert a character to its uppercase equivalent
char toUpper(char ch) {
	return (ch >= 'a' && ch <= 'z') ? (ch - 'a' + 'A') : ch;
}

// Function to encrypt the plaintext using the OTP cipher
void stringEncryption(char *text, char *key, char *cipherText) {
	int len = strlen(key);
	int cipher[len];

	for (int i = 0; i < len; i++) {
    	cipher[i] = toUpper(text[i]) - 'A' + toUpper(key[i]) - 'A';
    	if (cipher[i] > 25) {
        	cipher[i] -= 26;
    	}
    	cipherText[i] = cipher[i] + 'A';
	}
	cipherText[len] = '\0';
}

// Function to decrypt the ciphertext using the OTP cipher
void stringDecryption(char *cipherText, char *key, char *plainText) {
	int len = strlen(key);
	int plain[len];

	for (int i = 0; i < len; i++) {
    	plain[i] = toUpper(cipherText[i]) - 'A' - (toUpper(key[i]) - 'A');
    	if (plain[i] < 0) {
        	plain[i] += 26;
    	}
    	plainText[i] = plain[i] + 'A';
	}
	plainText[len] = '\0';
}

// Main driver function
int main() {
	char plainText[1024];
	char key[1024];
	char cipherText[1024];
	char decryptedText[1024];

	printf("Enter the plaintext message: ");
	fgets(plainText, sizeof(plainText), stdin);
	plainText[strcspn(plainText, "\n")] = '\0';

	printf("Enter the key: ");
	fgets(key, sizeof(key), stdin);
	key[strcspn(key, "\n")] = '\0';

	if (strlen(plainText) != strlen(key)) {
    	printf("Error: The key must be the same length as the plaintext message.\n");
    	return 1;
	}

	stringEncryption(plainText, key, cipherText);
	stringDecryption(cipherText, key, decryptedText);

	printf("\nOriginal Message: %s\n", plainText);
	printf("Key: %s\n", key);
	printf("Encrypted Message: %s\n", cipherText);
	printf("Decrypted Message: %s\n", decryptedText);

	return 0;
}

