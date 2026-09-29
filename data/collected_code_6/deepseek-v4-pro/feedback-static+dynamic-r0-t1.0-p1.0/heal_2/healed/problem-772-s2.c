#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_words_with_length(const char* input, int k) {
    if (input == NULL || k <= 0) {
        return NULL;
    }
    
    size_t len = strnlen(input, 1000000);
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
                    if (j > 0) {
                        if (j < len) {
                            result[j++] = ' ';
                        }
                    }
                    size_t copy_len = (size_t)word_length;
                    if (j + copy_len <= len) {
                        memcpy(result + j, input + word_start, copy_len);
                        j += copy_len;
                    }
                }
                word_start = -1;
                word_length = 0;
            }
            if (i < len && j > 0 && j < len && result[j-1] != ' ') {
                result[j++] = ' ';
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
    char input[1001];
    int k;
    
    printf("Enter a string: ");
    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    size_t newline_pos = strcspn(input, "\n");
    if (newline_pos < sizeof(input)) {
        input[newline_pos] = '\0';
    }
    
    printf("Enter length k: ");
    if (scanf("%d", &k) != 1) {
        return 1;
    }
    
    if (k < 0) {
        k = 0;
    }
    
    char* result = remove_words_with_length(input, k);
    if (result == NULL) {
        printf("Error processing string\n");
        return 1;
    }
    
    printf("Result: %s\n", result);
    
    free(result);
    return 0;
}