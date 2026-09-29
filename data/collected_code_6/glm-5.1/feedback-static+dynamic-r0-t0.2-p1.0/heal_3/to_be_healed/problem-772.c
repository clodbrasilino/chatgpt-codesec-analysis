#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

char* remove_words_of_length_k(const char* str, long k) {
    if (str == NULL || k <= 0) {
        char* result = malloc(1);
        if (result == NULL) {
            return NULL;
        }
        result[0] = '\0';
        return result;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char* result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;

    while (str[i] != '\0') {
        if (isalpha((unsigned char)str[i])) {
            size_t word_start = i;
            while (isalpha((unsigned char)str[i])) {
                i++;
            }
            size_t word_len = i - word_start;

            if (word_len != (size_t)k) {
                if (j + word_len <= len) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + j, str + word_start, word_len);
                    j += word_len;
                }
            }
        } else {
            if (j < len) {
                result[j++] = str[i++];
            } else {
                i++;
            }
        }
    }

    result[j] = '\0';
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <k>\n", argv[0]);
        return 1;
    }

    const char* input = argv[1];
    char* endptr;
    errno = 0;
    long k = strtol(argv[2], &endptr, 10);

    if (endptr == argv[2] || *endptr != '\0' || errno == ERANGE || k <= 0 || k > LONG_MAX) {
        fprintf(stderr, "Error: k must be a positive integer within valid range.\n");
        return 1;
    }

    char* output = remove_words_of_length_k(input, k);
    if (output == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1;
    }

    printf("%s\n", output);
    free(output);

    return 0;
}