#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

char* remove_k_length_words(const char* str, int k) {
    if (str == NULL || k < 0) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t res_idx = 0;
    size_t i = 0;

    while (str[i] != '\0') {
        if (isalpha((unsigned char)str[i])) {
            size_t word_start = i;
            size_t word_len = 0;

            while (str[i] != '\0' && isalpha((unsigned char)str[i])) {
                word_len++;
                i++;
            }

            if (word_len != (size_t)k) {
                if (res_idx + word_len <= len) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + res_idx, str + word_start, word_len);
                }
                res_idx += word_len;
            }
        } else {
            if (res_idx <= len) {
                result[res_idx++] = str[i];
            }
            i++;
        }
    }

    if (res_idx <= len) {
        result[res_idx] = '\0';
    } else {
        result[len] = '\0';
    }

    char* temp = (char*)realloc(result, res_idx + 1);
    if (temp != NULL) {
        result = temp;
    }

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char* const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <k>\n", argv[0]);
        return 1;
    }

    char* endptr;
    long k_long = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || k_long < 0 || k_long > INT_MAX) {
        fprintf(stderr, "Error: k must be a non-negative integer.\n");
        return 1;
    }

    int k = (int)k_long;

    char* modified_str = remove_k_length_words(argv[1], k);
    if (modified_str == NULL) {
        fprintf(stderr, "Error: Memory allocation failed or invalid input.\n");
        return 1;
    }

    printf("%s\n", modified_str);

    free(modified_str);

    return 0;
}