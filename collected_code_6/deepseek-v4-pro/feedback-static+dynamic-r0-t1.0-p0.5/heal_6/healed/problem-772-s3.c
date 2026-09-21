#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_words_with_length(char* str, int k) {
    if (str == NULL || k <= 0) {
        return NULL;
    }

    size_t len = strnlen(str, 4096);
    if (len == 0 || len >= 4096) {
        char* empty = (char*)malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    size_t max_result_size = len + 1;
    char* result = (char*)malloc(max_result_size);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    int word_start = -1;
    int word_length = 0;
    int first_word = 1;

    while (i <= len) {
        if (i < len && isalnum((unsigned char)str[i])) {
            if (word_start == -1) {
                word_start = (int)i;
            }
            word_length++;
        } else {
            if (word_start != -1) {
                if (word_length != k) {
                    if (!first_word) {
                        if (j < max_result_size - 1) {
                            result[j++] = ' ';
                        }
                    }
                    first_word = 0;

                    size_t space_left = max_result_size - j - 1;
                    size_t to_copy = (size_t)word_length;
                    if (to_copy > space_left) {
                        to_copy = space_left;
                    }
                    if (to_copy > 0 && j < max_result_size && word_start >= 0 && 
                        (size_t)word_start + to_copy <= len && j + to_copy <= max_result_size) {
                        memcpy(result + j, str + word_start, to_copy);
                        j += to_copy;
                    }
                }
                word_start = -1;
                word_length = 0;
            }
        }
        i++;
    }

    if (j < max_result_size) {
        result[j] = '\0';
    } else {
        result[max_result_size - 1] = '\0';
    }
    
    return result;
}

int main(void) {
    char input[] = "This is a test string with words of different lengths";
    int k = 2;
    
    char* result = remove_words_with_length(input, k);
    if (result != NULL) {
        printf("Original: %s\n", input);
        printf("After removing %d-letter words: %s\n", k, result);
        free(result);
    } else {
        printf("Memory allocation failed\n");
    }
    
    return 0;
}