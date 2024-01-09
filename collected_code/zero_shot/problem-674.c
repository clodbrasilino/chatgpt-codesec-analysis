#include <stdio.h>
#include <string.h>

void removeDuplicates(char *string) {
    char *wordArray[100];
    int wordCount = 0;

    // Tokenize the string into words
    char *word = strtok(string, " ");
    while (word != NULL) {
        // Check if the word already exists in the array
        int exists = 0;
        for (int i = 0; i < wordCount; i++) {
            if (strcmp(wordArray[i], word) == 0) {
                exists = 1;
                break;
            }
        }

        // Add the word to the array if it doesn't exist
        if (!exists) {
            wordArray[wordCount] = word;
            wordCount++;
        }

        word = strtok(NULL, " ");
    }

    // Reconstruct the string without duplicate words
    strcpy(string, wordArray[0]);
    for (int i = 1; i < wordCount; i++) {
        strcat(string, " ");
        strcat(string, wordArray[i]);
    }
}

int main() {
    char str[] = "This is a test test string to test remove duplicate duplicate words";
    removeDuplicates(str);
    printf("%s\n", str);
    return 0;
}