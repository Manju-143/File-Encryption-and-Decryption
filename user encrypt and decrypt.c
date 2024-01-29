#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 256

void encryptFile(const char *filename);
void decryptFile(const char *filename);

int main() {
    int choice;
    char filename[MAX];

    /* Get the operation choice from the user */
    printf("Choose operation:\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Hi please enter your choice (1 or 2): ");
    scanf("%d", &choice);

    /* Get the file name from the user */
    printf("Enter your file name:");
    scanf("%s", filename);

    switch (choice) {
        case 1:
            encryptFile(filename);
            break;
        case 2:
            decryptFile(filename);
            break;
        default:
            printf("Invalid choice. Please enter 1 or 2.\n");
            break;
    }

    return 0;
}

void encryptFile(const char *filename) {
    FILE *fp1, *fp2;
    int ch;
    char encryptedFilename[MAX];

    /* open the given file in read mode */
    fp1 = fopen(filename, "r");

    /* error handling */
    if (!fp1) {
        printf("Unable to open the input file!!\n");
        return;
    }

    /* create a file to save encrypted data */
    strcpy(encryptedFilename, filename);
    strcat(encryptedFilename, "_rot13.txt");
    fp2 = fopen(encryptedFilename, "w");

    /* error handling */
    if (!fp2) {
        printf("Unable to open the encrypted file!!\n");
        fclose(fp1);
        return;
    }

    /* converting plain text to ROT13 cipher text */
    while ((ch = fgetc(fp1)) != EOF) {
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            ch = (ch - base + 13) % 26 + base;
        }
        fprintf(fp2, "%c", ch);
    }

    /* closing all opened files */
    fclose(fp1);
    fclose(fp2);

    printf("\nROT13 Encryption completed. Encrypted text saved in %s.\n", encryptedFilename);
}

void decryptFile(const char *filename) {
    FILE *fp2;
    int ch;
    char decryptedFilename[MAX];

    /* open the encrypted file in read mode */
    fp2 = fopen(filename, "r");

    /* error handling */
    if (!fp2) {
        printf("Unable to open the encrypted file!!\n");
        return;
    }

    /* create a file to save decrypted data */
    strcpy(decryptedFilename, filename);
    strcat(decryptedFilename, "_decrypted.txt");
    FILE *fp3 = fopen(decryptedFilename, "w");

    /* error handling */
    if (!fp3) {
        printf("Unable to open the decrypted file!!\n");
        fclose(fp2);
        return;
    }

    /*
     * converting the ROT13 encrypted text to plain
     * text and writing it to the decrypted file
     */
    while ((ch = fgetc(fp2)) != EOF) {
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            ch = (ch - base + 13) % 26 + base;
        }
        fprintf(fp3, "%c", ch);
    }

    /* closing all opened files */
    fclose(fp2);
    fclose(fp3);

    printf("\nROT13 Decryption completed. Decrypted text saved in %s.\n", decryptedFilename);
}

