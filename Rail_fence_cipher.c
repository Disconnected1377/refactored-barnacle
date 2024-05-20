#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1000

// Function to encrypt the message using Rail Fence Cipher
void encryptRailFence(char* plaintext, int rails, char* ciphertext) {
	int len = strlen(plaintext);
	char rail[rails][len];
	int dir_down = 0;
	int row = 0, col = 0;

	// Initialize the rail matrix to '\n' (newline character)
	for (int i = 0; i < rails; i++)
    	for (int j = 0; j < len; j++)
        	rail[i][j] = '\n';

	// Build the rail matrix
	for (int i = 0; i < len; i++) {
    	if (row == 0 || row == rails - 1)
        	dir_down = !dir_down;

    	rail[row][col++] = plaintext[i];

    	dir_down ? row++ : row--;
	}

	// Construct the ciphertext
	int index = 0;
	for (int i = 0; i < rails; i++)
    	for (int j = 0; j < len; j++)
        	if (rail[i][j] != '\n')
            	ciphertext[index++] = rail[i][j];
	ciphertext[index] = '\0';
}

// Function to decrypt the message using Rail Fence Cipher
void decryptRailFence(char* ciphertext, int rails, char* plaintext) {
	int len = strlen(ciphertext);
	char rail[rails][len];
	int dir_down;
	int row = 0, col = 0;

	// Initialize the rail matrix to '\n' (newline character)
	for (int i = 0; i < rails; i++)
    	for (int j = 0; j < len; j++)
        	rail[i][j] = '\n';

	// Mark the positions to be filled
	for (int i = 0; i < len; i++) {
    	if (row == 0)
        	dir_down = 1;
    	if (row == rails - 1)
        	dir_down = 0;

    	rail[row][col++] = '*';

    	dir_down ? row++ : row--;
	}

	// Fill the rail matrix with ciphertext
	int index = 0;
	for (int i = 0; i < rails; i++)
    	for (int j = 0; j < len; j++)
        	if (rail[i][j] == '*' && index < len)
            	rail[i][j] = ciphertext[index++];

	// Read the rail matrix to construct the plaintext
	row = 0, col = 0;
	for (int i = 0; i < len; i++) {
    	if (row == 0)
        	dir_down = 1;
    	if (row == rails - 1)
        	dir_down = 0;

    	if (rail[row][col] != '*')
        	plaintext[i] = rail[row][col++];

    	dir_down ? row++ : row--;
	}
	plaintext[len] = '\0';
}

int main() {
	char message[MAX_LEN], encrypted[MAX_LEN], decrypted[MAX_LEN];
	int rails;

	printf("Enter the number of rails: ");
	scanf("%d", &rails);
	getchar();  // Clear the newline character from the input buffer

	printf("Enter the message: ");
	fgets(message, sizeof(message), stdin);
	message[strcspn(message, "\n")] = '\0';  // Remove the newline character

	encryptRailFence(message, rails, encrypted);
	decryptRailFence(encrypted, rails, decrypted);

	printf("\nOriginal Message: %s\n", message);
	printf("Number of Rails: %d\n", rails);
	printf("Encrypted Message: %s\n", encrypted);
	printf("Decrypted Message: %s\n", decrypted);

	return 0;
}

