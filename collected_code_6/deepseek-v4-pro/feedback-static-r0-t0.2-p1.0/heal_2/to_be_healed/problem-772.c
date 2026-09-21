#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_words_with_length(const char *str, int k) {
    if (str == NULL || k <= 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;

    while (i < len) {
        while (i < len && isspace((unsigned char)str[i])) {
            result[j++] = str[i++];
        }

        size_t start = i;
        while (i < len && !isspace((unsigned char)str[i])) {
            i++;
        }

        size_t word_len = i - start;
        if (word_len != (size_t)k) {
            for (size_t m = start; m < i; m++) {
                result[j++] = str[m];
            }
        }
    }

    result[j] = '\0';
    
    char *trimmed = (char *)realloc(result, j + 1);
    if (trimmed != NULL) {
        result = trimmed;
    }
    
    return result;
}

int main(void) {
    char input[] = "This is a test string with words of different lengths";
    int k = 2;

    char *result = remove_words_with_length(input, k);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Original: %s\n", input);
    printf("After removing words of length %d: %s\n", k, result);

    free(result);
    return 0;
}