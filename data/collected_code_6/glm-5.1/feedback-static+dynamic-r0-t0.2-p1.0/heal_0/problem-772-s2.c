#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_k_length_words(const char* str, int k) {
    if (str == NULL || k <= 0) {
        char* empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t len = strlen(str);
    char* result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t res_idx = 0;
    size_t i = 0;

    while (str[i] != '\0') {
        if (isspace((unsigned char)str[i])) {
            result[res_idx++] = str[i++];
        } else {
            size_t word_start = i;
            while (str[i] != '\0' && !isspace((unsigned char)str[i])) {
                i++;
            }
            size_t word_len = i - word_start;
            if (word_len != (size_t)k) {
                for (size_t j = word_start; j < i; j++) {
                    result[res_idx++] = str[j];
                }
            }
        }
    }

    result[res_idx] = '\0';
    return result;
}

int main() {
    const char* input = "This is a test string for removing words";
    int k = 4;
    
    char* output = remove_k_length_words(input, k);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Original: \"%s\"\n", input);
    printf("Modified: \"%s\"\n", output);

    free(output);
    output = NULL;

    return 0;
}