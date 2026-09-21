#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

void replace_with_colon(char *str, size_t max_len)
{
    size_t i;
    size_t len;

    if (str == NULL) {
        return;
    }

    len = strnlen(str, max_len);
    for (i = 0; i < len; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
}

int main(void)
{
    const char original[] = "Hello, world. This is a test.";
    char *buffer;
    size_t len;
    size_t size;

    len = strnlen(original, MAX_STR_LEN);
    if (len >= MAX_STR_LEN) {
        fprintf(stderr, "Input string too long or not terminated\n");
        return EXIT_FAILURE;
    }

    size = len + 1;
    if (size < len) {
        fprintf(stderr, "Size overflow detected\n");
        return EXIT_FAILURE;
    }

    buffer = malloc(size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (len >= size) {
        fprintf(stderr, "Destination buffer too small\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    memcpy(buffer, original, len);
    buffer[len] = '\0';

    replace_with_colon(buffer, size);

    if (printf("Original: %s\n", original) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    if (printf("Modified: %s\n", buffer) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}