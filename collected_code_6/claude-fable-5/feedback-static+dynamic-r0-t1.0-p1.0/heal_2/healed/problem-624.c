#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096

char *string_to_upper(char *str)
{
    size_t i;

    if (str == NULL) {
        return NULL;
    }

    for (i = 0; str[i] != '\0'; i++) {
        str[i] = (char)toupper((unsigned char)str[i]);
    }

    return str;
}

int main(void)
{
    static const char source[] = "Hello, World! 123 abc";
    size_t len;
    size_t buffer_size;
    char *buffer;

    len = strnlen(source, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        fprintf(stderr, "Input string too long or not terminated\n");
        return EXIT_FAILURE;
    }

    buffer_size = len + 1;
    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (len >= buffer_size) {
        fprintf(stderr, "Buffer too small for copy\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    memcpy(buffer, source, len);
    buffer[len] = '\0';

    if (string_to_upper(buffer) == NULL) {
        fprintf(stderr, "Conversion failed\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (printf("Original:  %s\n", source) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    if (printf("Uppercase: %s\n", buffer) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}