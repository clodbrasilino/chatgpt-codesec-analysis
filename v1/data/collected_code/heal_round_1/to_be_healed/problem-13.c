#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100

void countMostCommonWords(char *dictionary[], int size) {
    int wordCount[MAX_WORDS] = {0};
    int maxCount = 0;

    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'dictionary[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        char *currentWord = dictionary[i];
        int currentCount = 0;

        for (int j = 0; j < size; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'dictionary[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'currentWord' is initialized [premium-bughuntingUninit]
             */
            if (strcmp(currentWord, dictionary[j]) == 0) {
                currentCount++;
            }
        }

        wordCount[i] = currentCount;

        if (currentCount > maxCount) {
            maxCount = currentCount;
        }
    }

    printf("Most common word(s):");

    for (int i = 0; i < size; i++) {
        if (wordCount[i] == maxCount) {
            /* Possible weaknesses found:
             *  Cannot determine that 'dictionary[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf(" %s", dictionary[i]);
        }
    }

    printf("\n");
}

int main() {
    char *dictionary[] = {
        "apple",
        "banana",
        "apple",
        "orange",
        "apple",
        "banana",
        "grape"
    };
    int size = sizeof(dictionary) / sizeof(dictionary[0]);

    countMostCommonWords(dictionary, size);

    return 0;
}