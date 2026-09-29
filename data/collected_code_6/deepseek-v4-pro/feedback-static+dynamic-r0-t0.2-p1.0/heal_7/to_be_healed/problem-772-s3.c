#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_words_with_length(char* str, size_t max_len, int k) {
    if (str == NULL || k <= 0 || max_len == 0) {
        return str;
    }

    size_t len = strnlen(str, max_len);
    if (len >= max_len) {
        return NULL;
    }

    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    while (i < len) {
        while (i < len && isspace((unsigned char)str[i])) {
            if (j < len) {
                result[j++] = str[i++];
            } else {
                free(result);
                return NULL;
            }
        }

        if (i >= len) {
            break;
        }

        size_t word_start = i;
        while (i < len && !isspace((unsigned char)str[i])) {
            i++;
        }
        size_t word_length = i - word_start;

        if (word_length != (size_t)k) {
            if (j + word_length < len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + j, str + word_start, word_length);
                j += word_length;
            } else {
                free(result);
                return NULL;
            }
        }
    }

    if (j < len) {
        result[j] = '\0';
    } else {
        free(result);
        return NULL;
    }

    size_t result_len = j + 1;
    if (result_len <= max_len) {
        memmove(str, result, result_len);
    }
    free(result);
    return str;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[256];
    const char *source = "This is a test string with words of various lengths";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t source_len = strlen(source);
    
    if (source_len < sizeof(str)) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str, source, source_len + 1);
    } else {
        memcpy(str, source, sizeof(str) - 1);
        str[sizeof(str) - 1] = '\0';
    }
    
    int k = 2;
    
    printf("Original: %s\n", str);
    remove_words_with_length(str, sizeof(str), k);
    printf("After removing words of length %d: %s\n", k, str);
    
    return 0;
}