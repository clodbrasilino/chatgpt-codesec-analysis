#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_words_with_length(char* str, int k) {
    if (str == NULL || k <= 0) {
        return str;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    while (i < len) {
        while (i < len && isspace((unsigned char)str[i])) {
            result[j++] = str[i++];
        }

        size_t word_start = i;
        while (i < len && !isspace((unsigned char)str[i])) {
            i++;
        }
        size_t word_length = i - word_start;

        if (word_length != (size_t)k) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + j, str + word_start, word_length);
            j += word_length;
        }
    }

    result[j] = '\0';
    memmove(str, result, j + 1);
    free(result);
    return str;
}

int main(void) {
    char str[] = "This is a test string with words of various lengths";
    int k = 2;
    
    printf("Original: %s\n", str);
    remove_words_with_length(str, k);
    printf("After removing words of length %d: %s\n", k, str);
    
    return 0;
}