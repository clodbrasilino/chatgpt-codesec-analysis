#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** split_at_uppercase(const char* str, int* count) {
    if (!str || !count) return NULL;

    int num_words = 0;
    int len = 0;

    while (str[len] != '\0') {
        len++;
    }
    
    if (len > 0) num_words = 1;
    for (int i = 1; i < len; i++) {
        if (isupper((unsigned char)str[i])) {
            num_words++;
        }
    }

    char** result = (char**)calloc(num_words, sizeof(char*));
    if (!result) return NULL;

    *count = 0;
    if (len == 0) return result;

    int start = 0;
    for (int i = 1; i <= len; i++) {
        if (i == len || isupper((unsigned char)str[i])) {
            int word_len = i - start;
            result[*count] = (char*)malloc((word_len + 1) * sizeof(char));
            if (!result[*count]) {
                for (int j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                *count = 0;
                return NULL;
            }
            
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[*count], &str[start], word_len);
            result[*count][word_len] = '\0';
            (*count)++;
            start = i;
        }
    }

    return result;
}

void free_split_result(char** result, int count) {
    if (!result) return;
    for (int i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char* test_str = "SplitThisStringAtUppercaseLetters";
    int count = 0;

    char** words = split_at_uppercase(test_str, &count);
    if (words) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", words[i]);
        }
        free_split_result(words, count);
    }

    return 0;
}