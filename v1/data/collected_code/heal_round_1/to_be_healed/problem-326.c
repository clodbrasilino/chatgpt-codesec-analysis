#include <stdio.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define MAX_STRING_LENGTH 1000

char* getMostFrequentWord(char** strings, int size) {
    int i, j, count, maxCount = 0;
    char* mostFrequentWord = NULL;
    char* currentWord = NULL;

    for (i = 0; i < size; i++) {
        count = 1;
        for (j = i + 1; j < size; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'strings[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'strings[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (strcmp(strings[i], strings[j]) == 0)
                count++;
        }

        if (count > maxCount) {
            maxCount = count;
            /* Possible weaknesses found:
             *  Cannot determine that 'strings[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            mostFrequentWord = strings[i];
        }
    }

    /* Possible weaknesses found:
     *  Cannot determine that 'mostFrequentWord' is initialized [premium-bughuntingUninit]
     */
    return mostFrequentWord;
}

int main() {
    char* strings[] = {"apple", "banana", "apple", "orange", "banana", "apple"};
    int size = sizeof(strings) / sizeof(strings[0]);

    char* mostFrequentWord = getMostFrequentWord(strings, size);

    if (mostFrequentWord)
        printf("The word with most occurrences is: %s\n", mostFrequentWord);
    else
        printf("No word found.\n");

    return 0;
}