#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** split_at_uppercase(const char* str, int* count) {
    if (!str || !count) return NULL;

    int num_words = 0;
    int len = 0;
    
    if (str[0] != '\0') {
        num_words = 1;
        while (str[len] != '\0') {
            if (len > 0 && isupper((unsigned char)str[len])) {
                num_words++;
            }
            len++;
        }
    }

    char** result = (char**)malloc((num_words + 1) * sizeof(char*));
    if (!result) return NULL;

    *count = num_words;
    if (num_words == 0) {
        result[0] = NULL;
        return result;
    }

    int word_idx = 0;
    size_t start_idx = 0;

    for (size_t i = 1; i <= (size_t)len; i++) {
        if (i == (size_t)len || isupper((unsigned char)str[i])) {
            size_t word_len = i - start_idx;
            result[word_idx] = (char*)malloc((word_len + 1) * sizeof(char));
            if (!result[word_idx]) {
                for (int j = 0; j < word_idx; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(result[word_idx], str + start_idx, word_len);
            result[word_idx][word_len] = '\0';
            word_idx++;
            start_idx = i;
        }
    }
    
    result[word_idx] = NULL;
    return result;
}

void free_string_array(char** arr, int count) {
    if (!arr) return;
    for (int i = 0; i < count; i++) {
        free(arr[i]);
    }
    free(arr);
}

int main(void) {
    const char* test_str = "SplitThisStringAtUppercaseLetters";
    int count = 0;

    char** words = split_at_uppercase(test_str, &count);
    
    if (words) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", words[i]);
        }
        free_string_array(words, count);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return 1;
    }

    return 0;
}