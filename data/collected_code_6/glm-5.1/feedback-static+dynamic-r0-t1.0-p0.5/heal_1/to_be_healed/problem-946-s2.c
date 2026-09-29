#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int count;
} WordCount;

char *str_dup(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str) + 1;
    char *copy = malloc(len);
    if (copy) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, str, len);
    }
    return copy;
}

void find_most_common(const char *text, WordCount **results, int *result_count) {
    WordCount *words = NULL;
    int capacity = 0;
    int size = 0;

    const char *ptr = text;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    /* Possible weaknesses found:
     *  The scope of the variable 'buf_idx' can be reduced. [variableScope]
     */
    int buf_idx;

    while (*ptr) {
        while (*ptr && !isalpha((unsigned char)*ptr)) {
            ptr++;
        }
        if (!*ptr) {
            break;
        }

        buf_idx = 0;
        while (*ptr && isalpha((unsigned char)*ptr)) {
            if (buf_idx < (int)sizeof(buffer) - 1) {
                buffer[buf_idx++] = tolower((unsigned char)*ptr);
            }
            ptr++;
        }
        buffer[buf_idx] = '\0';

        int found = 0;
        for (int i = 0; i < size; i++) {
            if (strcmp(words[i].word, buffer) == 0) {
                words[i].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (size >= capacity) {
                int new_capacity = capacity == 0 ? 16 : capacity * 2;
                WordCount *new_words = realloc(words, new_capacity * sizeof(WordCount));
                if (!new_words) {
                    for (int i = 0; i < size; i++) {
                        free(words[i].word);
                    }
                    free(words);
                    *results = NULL;
                    *result_count = 0;
                    return;
                }
                words = new_words;
                capacity = new_capacity;
            }
            words[size].word = str_dup(buffer);
            if (!words[size].word) {
                for (int i = 0; i < size; i++) {
                    free(words[i].word);
                }
                free(words);
                *results = NULL;
                *result_count = 0;
                return;
            }
            words[size].count = 1;
            size++;
        }
    }

    if (size == 0) {
        *results = NULL;
        *result_count = 0;
        return;
    }

    int max_count = 0;
    for (int i = 0; i < size; i++) {
        if (words[i].count > max_count) {
            max_count = words[i].count;
        }
    }

    int top_count = 0;
    for (int i = 0; i < size; i++) {
        if (words[i].count == max_count) {
            top_count++;
        }
    }

    WordCount *top_words = malloc(top_count * sizeof(WordCount));
    if (!top_words) {
        for (int i = 0; i < size; i++) {
            free(words[i].word);
        }
        free(words);
        *results = NULL;
        *result_count = 0;
        return;
    }

    int idx = 0;
    for (int i = 0; i < size; i++) {
        if (words[i].count == max_count) {
            top_words[idx].word = words[i].word;
            top_words[idx].count = words[i].count;
            idx++;
        } else {
            free(words[i].word);
        }
    }

    free(words);
    *results = top_words;
    *result_count = top_count;
}

int main(void) {
    const char *text = "Hello world! Hello C developers. C is a great language, hello!";
    WordCount *results = NULL;
    int count = 0;

    find_most_common(text, &results, &count);

    if (count > 0 && results != NULL) {
        printf("Most common element(s) with count %d:\n", results[0].count);
        for (int i = 0; i < count; i++) {
            printf("- %s\n", results[i].word);
        }
    } else {
        printf("No words found.\n");
    }

    if (results != NULL) {
        for (int i = 0; i < count; i++) {
            free(results[i].word);
        }
        free(results);
    }

    return 0;
}