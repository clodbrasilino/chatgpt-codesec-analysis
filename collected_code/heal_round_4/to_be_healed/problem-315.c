#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int evenWordMaxLength(char *sentence) {
    if (sentence == NULL) {
        return 0;
    }
    
    int maxLength = 0;    
    char *clone = strdup(sentence);

    if(clone == NULL) {
        return 0;
    }

    char *word = strtok(clone, " "); 

    while (word != NULL) {
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        size_t length = strlen(word);

        if (length % 2 == 0 && length > (size_t)maxLength) {
            maxLength = (int)length;
        }

        word = strtok(NULL, " ");
    }
    
    free(clone);
    return maxLength;
}

int main() {
    const int MAX_SIZE = 256;
    char *sentence = malloc(MAX_SIZE * sizeof(char));
    if(sentence == NULL) {
        printf("Failed to allocate memory.\n");
        return 1;
    }

    printf("Enter a sentence: ");
    if (fgets(sentence, MAX_SIZE, stdin) == NULL) {
        printf("Failed to read a line.\n");
        free(sentence);
        return 1;
    }

    sentence[strcspn(sentence, "\n")] = '\0';

    int maxLength = evenWordMaxLength(sentence);
    printf("The maximum length of an even word is: %d\n", maxLength);

    free(sentence);
    return 0;
}