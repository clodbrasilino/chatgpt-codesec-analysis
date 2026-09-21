#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD_BUFFER_SIZE 256

static char *duplicate_word(const char *word, size_t len) {
    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, word, len);
    copy[len] = '\0';
    return copy;
}

static int starts_with_vowel(const char *word) {
    /* Possible weaknesses found:
     *  Uninitialized variable: word [uninitvar]
     *  Uninitialized variable: word
     */
    return word[0] == 'a' || word[0] == 'e' ||
           word[0] == 'A' || word[0] == 'E';
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

    while (*p) {
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (isalpha((unsigned char)*p)) {
            if (word_len < WORD_BUFFER_SIZE - 1) {
                word[word_len++] = *p;
            } else {
                for (int i = 0; i < *count; i++) {
                    free(words[i]);
                }
                free(words);
                return NULL;
            }
        } else {
            if (word_len > 0 && starts_with_vowel(word)) {
                if (*count >= capacity) {
                    int new_capacity = capacity * 2;
                    if (new_capacity < capacity) {
                        for (int i = 0; i < *count; i++) {
                            free(words[i]);
                        }
                        free(words);
                        return NULL;
                    }
                    char **temp = realloc(words, (size_t)new_capacity * sizeof(char *));
                    if (temp == NULL) {
                        for (int i = 0; i < *count; i++) {
                            free(words[i]);
                        }
                        free(words);
                        return NULL;
                    }
                    words = temp;
                    capacity = new_capacity;
                }
                words[*count] = duplicate_word(word, word_len);
                if (words[*count] == NULL) {
                    for (int i = 0; i < *count; i++) {
                        free(words[i]);
                    }
                    free(words);
                    return NULL;
                }
                (*count)++;
            }
            word_len = 0;
        }
        p++;
    }

    /* Possible weaknesses found:
     *  Calling function 'starts_with_vowel', 1st argument 'word' value is <Uninit>
     */
    if (word_len > 0 && starts_with_vowel(word)) {
        if (*count >= capacity) {
            int new_capacity = capacity * 2;
            if (new_capacity < capacity) {
                for (int i = 0; i < *count; i++) {
                    free(words[i]);
                }
                free(words);
                return NULL;
            }
            char **temp = realloc(words, (size_t)new_capacity * sizeof(char *));
            if (temp == NULL) {
                for (int i = 0; i < *count; i++) {
                    free(words[i]);
                }
                free(words);
                return NULL;
            }
            words = temp;
            /* Possible weaknesses found:
             *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
             *  Value stored to 'capacity' is never read [deadcode.DeadStores]
             */
            capacity = new_capacity;
        }
        words[*count] = duplicate_word(word, word_len);
        if (words[*count] == NULL) {
            for (int i = 0; i < *count; i++) {
                free(words[i]);
            }
            free(words);
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