#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_words_with_length(char* str, int k) {
    if (str == NULL || k <= 0) {
        return str;
    }

    size_t len = strlen(str);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    size_t word_start = 0;
    int in_word = 0;

    while (i <= len) {
        if (isalnum((unsigned char)str[i]) || str[i] == '\'') {
            if (!in_word) {
                word_start = i;
                in_word = 1;
            }
        } else {
            if (in_word) {
                size_t word_len = i - word_start;
                if (word_len != (size_t)k) {
                    if (j > 0 && result[j-1] != ' ' && str[word_start-1] == ' ') {
                        result[j++] = ' ';
                    }
                    memcpy(result + j, str + word_start, word_len);
                    j += word_len;
                }
                in_word = 0;
            }
            if (str[i] == ' ' && j > 0 && result[j-1] != ' ') {
                result[j++] = ' ';
            }
        }
        i++;
    }

    while (j > 0 && result[j-1] == ' ') {
        j--;
    }
    result[j] = '\0';

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