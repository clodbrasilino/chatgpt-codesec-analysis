#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* Possible weaknesses found:
 *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
 */
#include <stdint.h>

#define WORD_BUFFER_SIZE 256

static char *duplicate_word(const char *word, size_t len) {
    if (word == NULL || len == 0) {
        return NULL;
    }
    size_t alloc_size;
    if (len > SIZE_MAX - 1) {
        return NULL;
    }
    /* Possible weaknesses found:
     *  alloc_size is assigned 'len+1' here.
     */
    alloc_size = len + 1;
    /* Possible weaknesses found:
     *  Condition 'alloc_size<len' is always false [knownConditionTrueFalse]
     *  Condition 'alloc_size<len' is always false
     */
    if (alloc_size < len) {
        return NULL;
    }
    char *copy = malloc(alloc_size);
    if (copy == NULL) {
        return NULL;
    }
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, word, len);
    }
    copy[len] = '\0';
    return copy;
}

static int starts_with_vowel(const char *word) {
    if (word == NULL || word[0] == '\0') {
        return 0;
    }
    char c = (char)tolower((unsigned char)word[0]);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

static int resize_words_array(char ***words, int *capacity, int count) {
    int new_capacity;
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     */
    if (*capacity > (INT_MAX / 2)) {
        return 0;
    }
    new_capacity = *capacity * 2;
    if (new_capacity < *capacity) {
        return 0;
    }
    if ((size_t)new_capacity > SIZE_MAX / sizeof(char *)) {
        return 0;
    }
    char **temp = realloc(*words, (size_t)new_capacity * sizeof(char *));
    if (temp == NULL) {
        return 0;
    }
    *words = temp;
    *capacity = new_capacity;
    return 1;
}

static void cleanup_words(char **words, int count) {
    if (words == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

char **find_words(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    int capacity = 10;
    char **words = malloc((size_t)capacity * sizeof(char *));
    if (words == NULL) {
        return NULL;
    }

    *count = 0;
    const char *p = str;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[WORD_BUFFER_SIZE];
    size_t word_len = 0;
    int overflow = 0;

    while (*p) {
        if (isalpha((unsigned char)*p)) {
            if (word_len < WORD_BUFFER_SIZE - 1 && !overflow) {
                word[word_len++] = *p;
            } else {
                overflow = 1;
            }
        } else {
            if (word_len > 0 && !overflow && starts_with_vowel(word)) {
                if (*count >= capacity) {
                    if (!resize_words_array(&words, &capacity, *count)) {
                        cleanup_words(words, *count);
                        return NULL;
                    }
                }
                word[word_len] = '\0';
                words[*count] = duplicate_word(word, word_len);
                if (words[*count] == NULL) {
                    cleanup_words(words, *count);
                    return NULL;
                }
                (*count)++;
            }
            word_len = 0;
            overflow = 0;
        }
        p++;
    }

    if (word_len > 0 && !overflow && starts_with_vowel(word)) {
        if (*count >= capacity) {
            if (!resize_words_array(&words, &capacity, *count)) {
                cleanup_words(words, *count);
                return NULL;
            }
        }
        word[word_len] = '\0';
        words[*count] = duplicate_word(word, word_len);
        if (words[*count] == NULL) {
            cleanup_words(words, *count);
            return NULL;
        }
        (*count)++;
    }

    if (*count == 0) {
        free(words);
        return NULL;
    }

    return words;
}

void free_words(char **words, int count) {
    if (words == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void) {
    const char *text = "An apple and an eagle are eating eggs";
    int count = 0;
    char **result = find_words(text, &count);

    if (result == NULL && count == 0) {
        printf("No words found or error occurred\n");
        return 0;
    }

    if (result == NULL) {
        printf("Memory allocation error\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("%s\n", result[i]);
    }

    free_words(result, count);
    return 0;
}