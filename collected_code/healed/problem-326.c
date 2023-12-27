#include <stdio.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define MAX_STRING_LENGTH 1000

const char* getMostFrequentWord(const char** strings, int size) {
    int i, j, count, maxCount = 0;
    const char* mostFrequentWord = NULL;

    for (i = 0; i < size; i++) {
        count = 1;
        for (j = i + 1; j < size; j++) {
            if (strcmp(strings[i], strings[j]) == 0)
                count++;
        }

        if (count > maxCount) {
            maxCount = count;
            mostFrequentWord = strings[i];
        }
    }

    return mostFrequentWord;
}

int main() {
    const char* strings[] = {"apple", "banana", "apple", "orange", "banana", "apple"};
    int size = sizeof(strings) / sizeof(strings[0]);

    const char* mostFrequentWord = getMostFrequentWord(strings, size);

    if (mostFrequentWord)
        printf("The word with most occurrences is: %s\n", mostFrequentWord);
    else
        printf("No word found.\n");

    return 0;
}