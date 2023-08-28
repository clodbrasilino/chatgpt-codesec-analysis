#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100

void countMostCommonWords(char *dictionary[], int size) {
    int wordCount[MAX_WORDS] = {0};
    int maxCount = 0;

    for (int i = 0; i < size; i++) {
        char *currentWord = dictionary[i];
        int currentCount = 0;

        for (int j = 0; j < size; j++) {
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