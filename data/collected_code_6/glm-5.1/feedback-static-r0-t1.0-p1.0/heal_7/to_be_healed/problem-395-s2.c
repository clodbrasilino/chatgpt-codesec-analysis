#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHAR 256

char find_first_non_repeated(const char *str, size_t max_len) {
    size_t len = strnlen(str, max_len);
    if (len == 0) return '\0';

    unsigned int *counts = calloc(MAX_CHAR, sizeof(unsigned int));
    if (!counts) return '\0';

    for (size_t i = 0; i < len; ++i) {
        counts[(unsigned char)str[i]]++;
    }

    char result = '\0';
    for (size_t i = 0; i < len; ++i) {
        if (counts[(unsigned char)str[i]] == 1) {
            result = str[i];
            break;
        }
    }

    free(counts);
    return result;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    size_t argv1_len = strnlen(argv[1], MAX_CHAR);
    char *buf = malloc(argv1_len + 1);
    if (!buf) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buf, argv[1], argv1_len);
    buf[argv1_len] = '\0';

    char result = find_first_non_repeated(buf, MAX_CHAR);

    if (result == '\0') {
        printf("No non-repeated character found.\n");
    } else {
        printf("%c\n", result);
    }

    free(buf);
    return 0;
}