#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char* remove_words_with_length(const char* str, int k) {
    if (str == NULL || k <= 0) {
        return NULL;
    }

    size_t len = strlen(str);
    
    size_t max_len = len + 1;
    if (max_len > SIZE_MAX / sizeof(char)) {
        return NULL;
    }

    char* result = (char*)malloc(max_len);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    int word_length = 0;
    size_t word_start = 0;
    int in_word = 0;
    int first_word = 1;

    while (i <= len) {
        if (i < len && !isspace((unsigned char)str[i])) {
            if (!in_word) {
                word_start = i;
                in_word = 1;
            }
            word_length++;
        } else {
            if (in_word) {
                if (word_length != k) {
                    if (!first_word) {
                        if (j < max_len - 1) {
                            result[j++] = ' ';
                        }
                    }
                    first_word = 0;
                    
                    size_t remaining = max_len - j - 1;
                    size_t copy_len = (size_t)word_length;
                    if (copy_len > remaining) {
                        copy_len = remaining;
                    }
                    if (copy_len > 0 && j + copy_len < max_len) {
                        memcpy(result + j, str + word_start, copy_len);
                        j += copy_len;
                    }
                }
                in_word = 0;
                word_length = 0;
            }
        }
        i++;
    }

    if (j >= max_len) {
        j = max_len - 1;
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