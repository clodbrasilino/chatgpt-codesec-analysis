#include <stdio.h>
#include <string.h>

int evenWordMaxLength(char *sentence) {
    int maxLength = 0;
    /* Possible weaknesses found:
     *  Cannot determine that 'sentence[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    char *word = strtok(sentence, " ");

    while (word != NULL) {
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        int length = strlen(word);

        if (length % 2 == 0 && length > maxLength) {
            maxLength = length;
        }

        word = strtok(NULL, " ");
    }

    return maxLength;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char sentence[100];
    printf("Enter a sentence: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'sentence[0]' is initialized [premium-bughuntingUninit]
     */
    fgets(sentence, sizeof(sentence), stdin);

    sentence[strcspn(sentence, "\n")] = '\0';

    int maxLength = evenWordMaxLength(sentence);
    printf("The maximum length of an even word is: %d\n", maxLength);

    return 0;
}