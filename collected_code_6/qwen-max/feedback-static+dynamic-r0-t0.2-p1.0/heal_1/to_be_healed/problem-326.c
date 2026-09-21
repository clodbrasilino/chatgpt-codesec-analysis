#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;

int compare(const void *a, const void *b) {
    return ((WordCount *)b)->count - ((WordCount *)a)->count;
}

char* getMostFrequentWord(char *strings[], int size) {
    WordCount words[MAX_WORDS] = {0};
    int uniqueWords = 0;

    for (int i = 0; i < size; ++i) {
        /* Possible weaknesses found:
         * ASan: BUS
         */
        char *token = strtok(strings[i], " ");
        while (token != NULL) {
            int found = 0;
            for (int j = 0; j < uniqueWords; ++j) {
                if (strcmp(words[j].word, token) == 0) {
                    words[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(words[uniqueWords].word, token, MAX_WORD_LENGTH);
                words[uniqueWords].count = 1;
                uniqueWords++;
            }
            token = strtok(NULL, " ");
        }
    }

    qsort(words, uniqueWords, sizeof(WordCount), compare);

    if (uniqueWords > 0) {
        return words[0].word;
    } else {
        return "";
    }
}

int main() {
    char *strings[] = {
        "hello world",
        "hello there",
        "general kenobi",
        "hello again"
    };
    int size = sizeof(strings) / sizeof(strings[0]);

    char *mostFrequentWord = getMostFrequentWord(strings, size);
    printf("Most frequent word: %s\n", mostFrequentWord);

    return 0;
}