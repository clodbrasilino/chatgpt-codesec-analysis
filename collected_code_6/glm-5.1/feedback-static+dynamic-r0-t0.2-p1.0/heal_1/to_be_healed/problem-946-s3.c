#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int count;
} WordCount;

char *str_dup(const char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s) + 1;
    char *d = malloc(len);
    if (d) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(d, s, len);
    }
    return d;
}

void find_most_common(const char *text) {
    if (text == NULL) {
        return;
    }

    WordCount *words = NULL;
    size_t capacity = 0;
    size_t size = 0;

    const char *p = text;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    while (*p) {
        while (*p && !isalpha((unsigned char)*p)) {
            p++;
        }
        if (!*p) {
            break;
        }

        size_t i = 0;
        while (*p && isalpha((unsigned char)*p)) {
            if (i < sizeof(buffer) - 1) {
                buffer[i++] = tolower((unsigned char)*p);
            }
            p++;
        }
        buffer[i] = '\0';

        size_t j;
        int found = 0;
        for (j = 0; j < size; j++) {
            if (strcmp(words[j].word, buffer) == 0) {
                words[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (size >= capacity) {
                size_t new_capacity = capacity == 0 ? 16 : capacity * 2;
                WordCount *new_words = realloc(words, new_capacity * sizeof(WordCount));
                if (!new_words) {
                    for (j = 0; j < size; j++) {
                        free(words[j].word);
                    }
                    free(words);
                    return;
                }
                words = new_words;
                capacity = new_capacity;
            }
            words[size].word = str_dup(buffer);
            if (!words[size].word) {
                for (j = 0; j < size; j++) {
                    free(words[j].word);
                }
                free(words);
                return;
            }
            words[size].count = 1;
            size++;
        }
    }

    if (size == 0) {
        return;
    }

    int max_count = 0;
    size_t j;
    for (j = 0; j < size; j++) {
        if (words[j].count > max_count) {
            max_count = words[j].count;
        }
    }

    printf("Most common elements (count: %d):\n", max_count);
    for (j = 0; j < size; j++) {
        if (words[j].count == max_count) {
            printf("%s\n", words[j].word);
        }
    }

    for (j = 0; j < size; j++) {
        free(words[j].word);
    }
    free(words);
}

int main(void) {
    const char *text = "Hello world! This is a test. Hello, this test is only a test.";
    find_most_common(text);
    return 0;
}