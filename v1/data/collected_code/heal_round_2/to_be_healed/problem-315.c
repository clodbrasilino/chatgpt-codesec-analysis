#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int evenWordMaxLength(char *sentence) {
    if (sentence == NULL) {
        return 0;
    }
    
    int maxLength = 0;    
    char *word = strtok(sentence, " "); 

    while (word != NULL) {
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        size_t length = strlen(word);

        if (length % 2 == 0 && length > maxLength) {
            maxLength = length;
        }

        word = strtok(NULL, " ");
    }
    
    return maxLength;
}

int main() {
    const int MAX_SIZE = 256;
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char sentence[MAX_SIZE];
    memset(sentence, 0, MAX_SIZE);

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        printf("Failed to read a line.\n");
        return 1;
    }

    sentence[strcspn(sentence, "\n")] = '\0';

    int maxLength = evenWordMaxLength(sentence);
    printf("The maximum length of an even word is: %d\n", maxLength);

    return 0;
}