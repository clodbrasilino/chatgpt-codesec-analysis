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

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

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
            if (word_len != (size_t)k) {
                if (word_len > 0 && res_idx + word_len <= len) {
                    for (size_t j = 0; j < word_len; j++) {
                        result[res_idx + j] = str[word_start + j];
                    }
                    res_idx += word_len;
                }
            }
        } else {
            if (res_idx < len) {
                result[res_idx++] = str[i];
            }
            i++;
        }
    }

    result[res_idx] = '\0';
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <k>\n", argv[0]);
        return 1;
    }

    const char* input = argv[1];
    long k_long;
    char *endptr;

    errno = 0;
    k_long = strtol(argv[2], &endptr, 10);
    if (errno != 0 || endptr == argv[2] || *endptr != '\0' || k_long < 0 || k_long > INT_MAX) {
        fprintf(stderr, "k must be a valid non-negative integer\n");
        return 1;
    }
    int k = (int)k_long;

    char* output = remove_k_length_words(input, k);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed or invalid input\n");
        return 1;
    }

    printf("%s\n", output);
    free(output);

    return 0;
}