#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

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

    while (i < len) {
        if (isalpha((unsigned char)str[i])) {
            size_t word_start = i;
            while (i < len && isalpha((unsigned char)str[i])) {
                i++;
            }
            size_t word_len = i - word_start;

            if ((int)word_len != k) {
                size_t copy_len = word_len < (len + 1 - res_idx) ? word_len : (len + 1 - res_idx);
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + res_idx, str + word_start, copy_len);
                res_idx += copy_len;
            }
        } else {
            result[res_idx++] = str[i++];
        }
    }

    result[res_idx] = '\0';
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
    if (endptr == argv[2] || *endptr != '\0' || k_long < 0 || k_long > INT_MAX || errno == ERANGE) {
        fprintf(stderr, "Invalid input for k\n");
        return 1;
    }
    int k = (int)k_long;

    char* processed = remove_k_length_words(argv[1], k);

    if (processed == NULL) {
        fprintf(stderr, "Memory allocation failed or invalid input\n");
        return 1;
    }

    printf("%s\n", processed);
    free(processed);

    return 0;
}