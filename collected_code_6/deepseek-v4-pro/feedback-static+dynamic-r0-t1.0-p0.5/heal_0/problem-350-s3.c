#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *minimize_string(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        char *empty = (char *)malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    int freq[256] = {0};
    for (size_t i = 0; i < len; i++) {
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

    size_t new_len = len - (size_t)max_freq;
    char *result = (char *)malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] != target) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *input = "aabbbcc";
    char *output = minimize_string(input);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    printf("Original: %s\n", input);
    printf("Minimized: %s\n", output);
    free(output);
    return EXIT_SUCCESS;
}