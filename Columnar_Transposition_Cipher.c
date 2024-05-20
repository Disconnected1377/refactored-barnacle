#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
char* encryptMessage(int no_rows, int len_key, int len_msg, char* msg, int col_val[]);
char* decryptMessage(int no_rows, int len_key, char* cipher, int col_val[]);
void getColumnOrder(char* key, int* col_val);

// Main function
int main() {
	char msg[1000];
	char key[100];
    
	// Input the message to encrypt
	printf("Enter the message to encrypt: ");
	fgets(msg, sizeof(msg), stdin);
	msg[strcspn(msg, "\n")] = '\0'; // Remove trailing newline

	// Input the keyword
	printf("Enter the keyword: ");
	fgets(key, sizeof(key), stdin);
	key[strcspn(key, "\n")] = '\0'; // Remove trailing newline

	int len_key = strlen(key);
	int len_msg = strlen(msg);

	// Determine the column order based on the key
	int col_val[len_key];
	getColumnOrder(key, col_val);

	// Calculate the number of rows
	int no_rows = len_msg / len_key + (len_msg % len_key != 0);

	// Encrypt the message
	char* cipher_text = encryptMessage(no_rows, len_key, len_msg, msg, col_val);
	printf("\nEncrypted Message: %s\n", cipher_text);

	// Decrypt the message
	char* original_msg = decryptMessage(no_rows, len_key, cipher_text, col_val);
	printf("Decrypted Message: %s\n", original_msg);

	// Free allocated memory
	free(cipher_text);
	free(original_msg);

	return 0;
}

// Function to encrypt the message using Columnar Transposition Cipher
char* encryptMessage(int no_rows, int len_key, int len_msg, char* msg, int col_val[]) {
	int x = 0;
	char enc_mat[no_rows][len_key];
    
	// Creating the matrix and initializing with '_'
	for (int i = 0; i < no_rows; i++) {
    	for (int j = 0; j < len_key; j++) {
        	if (x < len_msg) {
            	enc_mat[i][j] = msg[x++];
        	} else {
            	enc_mat[i][j] = '_';
        	}
    	}
	}

	int t = 1;
	char* cipher = (char*)malloc((no_rows * len_key + 1) * sizeof(char));
	cipher[0] = '\0';

	// Finding the cipher text according to the value of col_val matrix
	while (t <= len_key) {
    	for (int i = 0; i < len_key; i++) {
        	if (col_val[i] == t) {
            	for (int j = 0; j < no_rows; j++) {
                	char temp[2] = {enc_mat[j][i], '\0'};
                	strcat(cipher, temp);
            	}
            	t++;
        	}
    	}
	}
    
	return cipher;
}

// Function to decrypt the message using Columnar Transposition Cipher
char* decryptMessage(int no_rows, int len_key, char* cipher, int col_val[]) {
	char dec_mat[no_rows][len_key];
	int x = 0, t = 1;

	// Rearrange the matrix according to the col_val
	while (t <= len_key) {
    	for (int i = 0; i < len_key; i++) {
        	if (col_val[i] == t) {
            	for (int j = 0; j < no_rows; j++) {
                	dec_mat[j][i] = cipher[x++];
            	}
            	t++;
        	}
    	}
	}

	char* message = (char*)malloc((no_rows * len_key + 1) * sizeof(char));
	message[0] = '\0';

	// Reconstruct the message from the matrix
	for (int i = 0; i < no_rows; i++) {
    	for (int j = 0; j < len_key; j++) {
        	char temp[2] = {dec_mat[i][j], '\0'};
        	strcat(message, temp);
    	}
	}
    
	// Replace underscores with spaces
	for (int i = 0; message[i] != '\0'; i++) {
    	if (message[i] == '_') {
        	message[i] = ' ';
    	}
	}

	return message;
}

// Function to determine the column order based on the key
void getColumnOrder(char* key, int* col_val) {
	int len_key = strlen(key);
	int val = 1, count = 0, ind;

	// Initialize col_val matrix with 0
	memset(col_val, 0, len_key * sizeof(int));

	// Numbering the key alphabets according to its ASCII value
	while (count < len_key) {
    	int min = 999;
    	for (int i = 0; i < len_key; i++) {
        	if ((min > (int)key[i]) && (col_val[i] == 0)) {
            	min = (int)key[i];
            	ind = i;
        	}
    	}
    	col_val[ind] = val++;
    	count++;
	}
}

