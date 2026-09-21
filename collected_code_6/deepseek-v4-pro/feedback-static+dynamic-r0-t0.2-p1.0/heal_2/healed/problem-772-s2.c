#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_words_with_length(const char* str, int k) {
    if (str == NULL || k <= 0) {
        return NULL;
    }

    size_t len = strlen(str);
    size_t result_size = len + 1;
    char* result = (char*)malloc(result_size);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    size_t word_start = 0;
    int in_word = 0;

    while (i <= len) {
        if (i < len && (isalnum((unsigned char)str[i]) || str[i] == '\'')) {
            if (!in_word) {
                word_start = i;
                in_word = 1;
            }
        } else {
            if (in_word) {
                size_t word_len = i - word_start;
                if (word_len != (size_t)k) {
                    if (j > 0 && result[j-1] != ' ' && word_start > 0 && str[word_start-1] == ' ') {
                        if (j < result_size) {
                            result[j++] = ' ';
                        }
                    }
                    if (j + word_len < result_size) {
                        size_t remaining = result_size - j;
                        size_t copy_len = (word_len < remaining) ? word_len : remaining;
                        memcpy(result + j, str + word_start, copy_len);
                        j += copy_len;
                    }
                }
                in_word = 0;
            }
            if (i < len && str[i] == ' ' && j > 0 && result[j-1] != ' ') {
                if (j < result_size) {
                    result[j++] = ' ';
                }
            }
        }
        i++;
    }

    while (j > 0 && result[j-1] == ' ') {
        j--;
    }
    
    if (j < result_size) {
        result[j] = '\0';
    } else {
        result[result_size - 1] = '\0';
    }

    char* final_result = (char*)realloc(result, j + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
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