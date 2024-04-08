#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants
#define MAX_FILE_NAME_LENGTH 100
#define MAX_KEY 26

// Function prototypes
void encryptFile(FILE *input, FILE *output, int key);
void decryptFile(FILE *input, FILE *output, int key);

int main(int argc, char *argv[]) {
    // Check for correct number of command-line arguments
    if (argc != 5) {
        printf("Usage: %s <encrypt/decrypt> <input_file> <output_file> <key>\n", argv[0]);
        return 1;
    }

    // Parse command-line arguments
    char *mode = argv[1];
    char *inputFileName = argv[2];
    char *outputFileName = argv[3];
    int key = atoi(argv[4]);

    // Check if key is within valid range
    if (key < 0 || key >= MAX_KEY) {
        printf("Key must be between 0 and %d\n", MAX_KEY - 1);
        return 1;
    }

    // Open input file
    FILE *inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        printf("Error: Unable to open input file '%s'\n", inputFileName);
        return 1;
    }

    // Open output file
    FILE *outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        printf("Error: Unable to open output file '%s'\n", outputFileName);
        fclose(inputFile);
        return 1;
    }

    // Perform encryption or decryption based on mode
    if (strcmp(mode, "encrypt") == 0) {
        encryptFile(inputFile, outputFile, key);
        printf("File encrypted successfully.\n");
    } else if (strcmp(mode, "decrypt") == 0) {
        decryptFile(inputFile, outputFile, key);
        printf("File decrypted successfully.\n");
    } else {
        printf("Invalid mode. Use 'encrypt' or 'decrypt'.\n");
    }

    // Close files
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

// Function to encrypt file
void encryptFile(FILE *input, FILE *output, int key) {
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        if (ch >= 'a' && ch <= 'z') {
            ch = 'a' + (ch - 'a' + key) % MAX_KEY;
        } else if (ch >= 'A' && ch <= 'Z') {
            ch = 'A' + (ch - 'A' + key) % MAX_KEY;
        }
        fputc(ch, output);
    }
}

// Function to decrypt file
void decryptFile(FILE *input, FILE *output, int key) {
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        if (ch >= 'a' && ch <= 'z') {
            ch = 'a' + (ch - 'a' - key + MAX_KEY) % MAX_KEY;
        } else if (ch >= 'A' && ch <= 'Z') {
            ch = 'A' + (ch - 'A' - key + MAX_KEY) % MAX_KEY;
        }
        fputc(ch, output);
    }
}


