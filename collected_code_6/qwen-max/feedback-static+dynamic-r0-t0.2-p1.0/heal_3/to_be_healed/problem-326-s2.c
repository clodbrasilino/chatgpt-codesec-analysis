#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LENGTH + 1];
    int count;
} WordCount;

int compare(const void *a, const void *b) {
    return ((WordCount *)b)->count - ((WordCount *)a)->count;
}

char* findMostFrequentWord(char *strings[], int size) {
    WordCount words[MAX_WORDS] = {0};
    int word_count = 0;

    for (int i = 0; i < size; ++i) {
        char *token = strtok(strings[i], " ");
        while (token != NULL) {
            int found = 0;
            for (int j = 0; j < word_count; ++j) {
                if (strcmp(words[j].word, token) == 0) {
                    words[j].count++;
                    found = 1;
                    break;
                }
            }
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            if (!found && strlen(token) < MAX_WORD_LENGTH) {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(words[word_count].word, token, MAX_WORD_LENGTH);
                words[word_count].word[MAX_WORD_LENGTH - 1] = '\0';
                words[word_count].count = 1;
                word_count++;
            }
            token = strtok(NULL, " ");
        }
    }

    qsort(words, word_count, sizeof(WordCount), compare);

    if (word_count > 0) {
        return strdup(words[0].word);
    } else {
        return NULL;
    }
}

int main() {
    char *strings[] = {
        "hello world",
        "hello there",
        "general kenobi",
        "hello general"
    };
    int size = sizeof(strings) / sizeof(strings[0]);

    char *most_frequent_word = findMostFrequentWord(strings, size);
    if (most_frequent_word) {
        printf("Most frequent word: %s\n", most_frequent_word);
        free(most_frequent_word);
    } else {
        printf("No words found.\n");
    }

    return 0;
}