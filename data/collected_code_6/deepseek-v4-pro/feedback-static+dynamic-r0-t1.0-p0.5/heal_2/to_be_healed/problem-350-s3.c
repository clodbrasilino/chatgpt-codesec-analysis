#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *minimize_string(const char *str, size_t str_len) {
    if (str == NULL) {
        return NULL;
    }

    if (str_len == 0) {
        char *empty = (char *)malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    int freq[256] = {0};
    for (size_t i = 0; i < str_len; i++) {
        freq[(unsigned char)str[i]]++;
    }

    char target = str[0];
    int max_freq = freq[(unsigned char)target];
    for (int i = 1; i < 256; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            target = (char)i;
        }
    }

    size_t new_len = str_len - (size_t)max_freq;
    char *result = (char *)malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < str_len; i++) {
        if (str[i] != target) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *input = "aabbbcc";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    char *output = minimize_string(input, input_len);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    printf("Original: %s\n", input);
    printf("Minimized: %s\n", output);
    free(output);
    return EXIT_SUCCESS;
}