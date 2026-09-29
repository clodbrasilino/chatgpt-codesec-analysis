#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_words_with_length(const char* input, int k) {
    if (input == NULL || k <= 0) {
        return NULL;
    }
    
    size_t len = strnlen(input, 1000000);
    if (len >= 1000000) {
        return NULL;
    }
    
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    size_t i = 0;
    size_t j = 0;
    int word_start = -1;
    int word_length = 0;
    
    while (i <= len) {
        if (i == len || isspace((unsigned char)input[i])) {
            if (word_start != -1) {
                if (word_length != k) {
                    if (j > 0 && j < len) {
                        result[j++] = ' ';
                    }
                    if (j + (size_t)word_length < len + 1) {
                        if ((size_t)word_length > len + 1 - j) {
                            free(result);
                            return NULL;
                        }
                        size_t dest_remaining = len + 1 - j;
                        if ((size_t)word_length > dest_remaining) {
                            free(result);
                            return NULL;
                        }
                        memcpy(result + j, input + word_start, (size_t)word_length);
                        j += (size_t)word_length;
                    } else {
                        free(result);
                        return NULL;
                    }
                }
                word_start = -1;
                word_length = 0;
            }
        } else {
            if (word_start == -1) {
                word_start = (int)i;
            }
            word_length++;
        }
        i++;
    }
    
    while (j > 0 && result[j-1] == ' ') {
        j--;
    }
    result[j] = '\0';
    
    char* final_result = (char*)realloc(result, j + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }
    
    return final_result;
}

int main(void) {
    char* input = NULL;
    size_t input_size = 0;
    int k;
    
    printf("Enter a string: ");
    if (getline(&input, &input_size, stdin) == -1) {
        free(input);
        return 1;
    }
    
    size_t input_len = strnlen(input, 2000);
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    }
    
    if (input_len > 1000) {
        free(input);
        return 1;
    }
    
    printf("Enter length k: ");
    if (scanf("%d", &k) != 1) {
        free(input);
        return 1;
    }
    
    if (k < 0) {
        k = 0;
    }
    
    char* result = remove_words_with_length(input, k);
    if (result == NULL) {
        printf("Error processing string\n");
        free(input);
        return 1;
    }
    
    printf("Result: %s\n", result);
    
    free(result);
    free(input);
    return 0;
}