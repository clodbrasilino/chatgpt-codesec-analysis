#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_words_with_length(const char* str, int k) {
    if (str == NULL || k <= 0) {
        return NULL;
    }

    size_t max_len = strnlen(str, 1000001);
    if (max_len > 1000000) {
        return NULL;
    }
    size_t len = max_len;

    size_t result_size = 0;
    size_t i = 0;
    int in_word = 0;
    size_t word_length = 0;

    while (i <= len) {
        if (i < len && isalnum((unsigned char)str[i])) {
            if (!in_word) {
                in_word = 1;
                word_length = 1;
            } else {
                word_length++;
            }
        } else {
            if (in_word) {
                if (word_length != (size_t)k) {
                    result_size += word_length + 1;
                }
                in_word = 0;
            }
        }
        i++;
    }

    if (result_size == 0) {
        char* empty = (char*)malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    result_size--;

    char* result = (char*)malloc(result_size + 1);
    if (result == NULL) {
        return NULL;
    }

    i = 0;
    size_t j = 0;
    in_word = 0;
    size_t word_start = 0;
    word_length = 0;
    int needs_space = 0;

    while (i <= len) {
        if (i < len && isalnum((unsigned char)str[i])) {
            if (!in_word) {
                word_start = i;
                in_word = 1;
                word_length = 1;
            } else {
                word_length++;
            }
        } else {
            if (in_word) {
                if (word_length != (size_t)k) {
                    if (needs_space) {
                        if (j >= result_size) {
                            free(result);
                            return NULL;
                        }
                        result[j++] = ' ';
                    }
                    if (word_length > result_size - j) {
                        free(result);
                        return NULL;
                    }
                    if (word_start + word_length > len) {
                        free(result);
                        return NULL;
                    }
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + j, str + word_start, word_length);
                    j += word_length;
                    needs_space = 1;
                }
                in_word = 0;
            }
        }
        i++;
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    const char* input = "hello world this is a test string";
    int k = 2;
    
    char* result = remove_words_with_length(input, k);
    if (result != NULL) {
        printf("Original: %s\n", input);
        printf("After removing words of length %d: %s\n", k, result);
        free(result);
    }

    return 0;
}