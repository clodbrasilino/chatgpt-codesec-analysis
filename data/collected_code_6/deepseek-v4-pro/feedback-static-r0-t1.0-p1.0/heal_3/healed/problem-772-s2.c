#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char* remove_words_with_length(const char* input, int k) {
    if (input == NULL || k <= 0) {
        return NULL;
    }
    
    size_t len = 0;
    while (input[len] != '\0') {
        if (len >= SIZE_MAX - 1) {
            return NULL;
        }
        len++;
    }
    
    if (len >= SIZE_MAX - 1) {
        return NULL;
    }
    
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    size_t i = 0;
    size_t j = 0;
    size_t word_start = 0;
    size_t word_length = 0;
    int in_word = 0;
    
    while (i <= len) {
        if (i == len || isspace((unsigned char)input[i])) {
            if (in_word) {
                if (word_length != (size_t)k) {
                    if (j > 0) {
                        if (j + 1 >= len + 1) {
                            free(result);
                            return NULL;
                        }
                        result[j++] = ' ';
                    }
                    if (j + word_length >= len + 1) {
                        free(result);
                        return NULL;
                    }
                    size_t copy_pos = j;
                    for (size_t m = 0; m < word_length; m++) {
                        result[copy_pos + m] = input[word_start + m];
                    }
                    j += word_length;
                }
                in_word = 0;
                word_length = 0;
            }
        } else {
            if (!in_word) {
                word_start = i;
                in_word = 1;
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
    char* line = NULL;
    size_t bufsize = 0;
    ssize_t line_len;
    int k;
    
    printf("Enter a string: ");
    line_len = getline(&line, &bufsize, stdin);
    if (line_len == -1) {
        free(line);
        return 1;
    }
    
    if (line_len > 0 && line[line_len - 1] == '\n') {
        line[line_len - 1] = '\0';
        line_len--;
    }
    
    printf("Enter length k: ");
    if (scanf("%d", &k) != 1) {
        free(line);
        return 1;
    }
    if (k <= 0) {
        printf("Error: k must be a positive integer\n");
        free(line);
        return 1;
    }
    
    if (line_len == 0) {
        char* result = (char*)malloc(1);
        if (result == NULL) {
            printf("Error processing string\n");
            free(line);
            return 1;
        }
        result[0] = '\0';
        printf("Result: %s\n", result);
        free(result);
        free(line);
        return 0;
    }
    
    char* result = remove_words_with_length(line, k);
    if (result == NULL) {
        printf("Error processing string\n");
        free(line);
        return 1;
    }
    
    printf("Result: %s\n", result);
    
    free(result);
    free(line);
    return 0;
}