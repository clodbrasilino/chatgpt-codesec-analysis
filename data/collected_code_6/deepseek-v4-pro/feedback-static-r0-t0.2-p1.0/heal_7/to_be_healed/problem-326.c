#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

static size_t safe_str_copy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        if (dest != NULL && dest_size > 0) {
            dest[0] = '\0';
        }
        return 0;
    }

    size_t i;
    for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return i;
}

static char *safe_strndup(const char *src, size_t max_len) {
    if (src == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (len < max_len && src[len] != '\0') {
        len++;
    }

    char *dest = (char *)malloc(len + 1);
    if (dest == NULL) {
        return NULL;
    }

    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, src, len);
    }
    dest[len] = '\0';
    return dest;
}

char *most_frequent_word(const char **strings, int n) {
    if (n <= 0 || strings == NULL) {
        return NULL;
    }

    WordCount *words = (WordCount *)calloc(MAX_WORDS, sizeof(WordCount));
    if (words == NULL) {
        return NULL;
    }

    int word_count = 0;
    int max_count = 0;
    int result_index = -1;

    for (int i = 0; i < n; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t str_len = strnlen(strings[i], MAX_WORD_LEN * MAX_WORDS);
        if (str_len >= MAX_WORD_LEN * MAX_WORDS) {
            free(words);
            return NULL;
        }

        char *copy = safe_strndup(strings[i], str_len);
        if (copy == NULL) {
            free(words);
            return NULL;
        }

        /* Possible weaknesses found:
         *  Segmentation fault: 11
         */
        char *token = strtok(copy, " \t\n\r.,;:!?\"'()[]{}");
        while (token != NULL) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char safe_token[MAX_WORD_LEN];
            safe_str_copy(safe_token, token, sizeof(safe_token));

            int found = 0;
            for (int j = 0; j < word_count; j++) {
                if (strcmp(words[j].word, safe_token) == 0) {
                    words[j].count++;
                    if (words[j].count > max_count) {
                        max_count = words[j].count;
                        result_index = j;
                    }
                    found = 1;
                    break;
                }
            }

            if (!found && word_count < MAX_WORDS) {
                safe_str_copy(words[word_count].word, safe_token, sizeof(words[word_count].word));
                words[word_count].count = 1;
                if (words[word_count].count > max_count) {
                    max_count = words[word_count].count;
                    result_index = word_count;
                }
                word_count++;
            }

            token = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
        }

        free(copy);
    }

    char *final_result = NULL;
    if (result_index >= 0 && result_index < word_count) {
        final_result = safe_strndup(words[result_index].word, MAX_WORD_LEN - 1);
    }

    free(words);
    return final_result;
}

int main(void) {
    const char *strings[] = {
        "hello world hello",
        "this is a test",
        "hello again world",
        "test test test"
    };
    int n = sizeof(strings) / sizeof(strings[0]);

    char *result = most_frequent_word(strings, n);
    if (result != NULL) {
        printf("Most frequent word: %s\n", result);
        free(result);
    } else {
        printf("No words found\n");
    }

    return 0;
}