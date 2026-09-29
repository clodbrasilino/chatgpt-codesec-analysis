#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

char* findFirstRepeatedWord(const char* input) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LENGTH + 1] = {0};
    int word_count = 0;
    const char* p = input;
    const char* start = p;

    while (*p) {
        if (*p == ' ' || *p == '\n' || *p == '\t') {
            if (start != p) {
                size_t len = p - start;
                if (len <= MAX_WORD_LENGTH) {
                    for (int i = 0; i < word_count; ++i) {
                        if (strncmp(words[i], start, len) == 0 && words[i][len] == '\0') {
                            return strdup(start);
                        }
                    }
                    if (word_count < MAX_WORDS) {
                        /* Possible weaknesses found:
                         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                         */
                        strncpy(words[word_count], start, len);
                        words[word_count][len] = '\0';
                        word_count++;
                    }
                } else {
                    return NULL;
                }
            }
            start = p + 1;
        }
        p++;
    }

    if (start != p) {
        size_t len = p - start;
        if (len <= MAX_WORD_LENGTH) {
            for (int i = 0; i < word_count; ++i) {
                if (strncmp(words[i], start, len) == 0 && words[i][len] == '\0') {
                    return strdup(start);
                }
            }
        }
    }

    return NULL;
}

int main() {
    const char* input = "This is a test test string to find the first repeated word";
    char* result = findFirstRepeatedWord(input);

    if (result) {
        printf("First repeated word: %s\n", result);
        free(result);
    } else {
        printf("No repeated words found.\n");
    }

    return 0;
}