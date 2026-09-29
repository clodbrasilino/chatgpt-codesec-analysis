#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t replace_chars(char *str, size_t n)
{
    size_t count = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; str[i] != '\0' && count < n; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
            count++;
        }
    }

    return count;
}

int main(void)
{
    static const char source[] = "Hello world, this is a test. Replace them all.";
    char *buffer;
    size_t buf_size;
    size_t len;
    size_t replaced;

    buf_size = sizeof(source);
    len = strnlen(source, buf_size - 1U);

    if (len >= buf_size) {
        fprintf(stderr, "Source length exceeds destination buffer\n");
        return EXIT_FAILURE;
    }

    buffer = malloc(buf_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (len + 1U > buf_size) {
        fprintf(stderr, "Copy would exceed destination buffer\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    memcpy(buffer, source, len);
    buffer[len] = '\0';

    replaced = replace_chars(buffer, 5U);

    if (printf("Original: %s\n", source) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }
    if (printf("Modified: %s\n", buffer) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }
    if (printf("Replacements made: %zu\n", replaced) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}