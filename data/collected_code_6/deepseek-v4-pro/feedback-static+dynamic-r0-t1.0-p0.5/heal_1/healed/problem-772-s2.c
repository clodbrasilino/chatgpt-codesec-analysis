#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_words_with_length(const char* input, int k) {
    if (input == NULL || k <= 0) {
        return NULL;
    }

    size_t len = strlen(input);
    size_t capacity = len + 1;
    char* result = (char*)malloc(capacity);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    size_t word_start = 0;
    size_t word_length = 0;
    int in_word = 0;

    while (input[i] != '\0') {
        if (isalnum((unsigned char)input[i])) {
            if (!in_word) {
                word_start = i;
                word_length = 1;
                in_word = 1;
            } else {
                word_length++;
            }
        } else {
            if (in_word) {
                if (word_length != (size_t)k) {
                    if (j > 0 && j + word_length + 1 < capacity) {
                        result[j++] = ' ';
                    }
                    if (j + word_length < capacity) {
                        memcpy(result + j, input + word_start, word_length);
                        j += word_length;
                    }
                }
                in_word = 0;
                word_length = 0;
            }
        }
        i++;
    }

    if (in_word) {
        if (word_length != (size_t)k) {
            if (j > 0 && j + word_length + 1 < capacity) {
                result[j++] = ' ';
            }
            if (j + word_length < capacity) {
                memcpy(result + j, input + word_start, word_length);
                j += word_length;
            }
        }
    }

    if (j >= capacity) {
        j = capacity - 1;
    }
    result[j] = '\0';

    char* final_result = (char*)realloc(result, j + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
}

int main() {
    char input[] = "This is a test string with words of different lengths";
    int k = 2;
    
    char* result = remove_words_with_length(input, k);
    if (result != NULL) {
        printf("Original: %s\n", input);
        printf("After removing words of length %d: %s\n", k, result);
        free(result);
    } else {
        printf("Error processing string\n");
    }

    char input2[] = "hello world this is a test";
    k = 5;
    result = remove_words_with_length(input2, k);
    if (result != NULL) {
        printf("Original: %s\n", input2);
        printf("After removing words of length %d: %s\n", k, result);
        free(result);
    } else {
        printf("Error processing string\n");
    }

    return 0;
}