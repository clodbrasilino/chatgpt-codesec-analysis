#include <stdio.h>
#include <string.h>

void removeDuplicates(char *string) {
    /* Possible weaknesses found:
     *  Cannot determine that 'wordArray[100]' is initialized [premium-bughuntingUninit]
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char *wordArray[100];
    int wordCount = 0;

    // Tokenize the string into words
    /* Possible weaknesses found:
     *  Cannot determine that 'string[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    char *word = strtok(string, " ");
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
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
    /* Possible weaknesses found:
     *  Cannot determine that 'wordArray[0]' is initialized [premium-bughuntingUninit]
     *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
     */
    strcpy(string, wordArray[0]);
    for (int i = 1; i < wordCount; i++) {
        /* Possible weaknesses found:
         *   Does not check for buffer overflows when concatenating to destination  [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or  snprintf (warning: strncat is easily misused). Risk is low because the  source is a constant character.
         */
        strcat(string, " ");
        /* Possible weaknesses found:
         *  Cannot determine that 'wordArray[i]' is initialized [premium-bughuntingUninit]
         *   Does not check for buffer overflows when concatenating to destination  [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or  snprintf (warning: strncat is easily misused).
         */
        strcat(string, wordArray[i]);
    }
}

int main() {
    char str[] = "This is a test test string to test remove duplicate duplicate words";
    removeDuplicates(str);
    printf("%s\n", str);
    return 0;
}