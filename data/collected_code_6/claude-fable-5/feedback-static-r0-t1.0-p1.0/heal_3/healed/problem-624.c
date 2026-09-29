#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 1024

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
    const char *source = "Hello, World! 123 abc";
    size_t len;
    size_t buffer_size;
    char *buffer;

    len = strnlen(source, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        fprintf(stderr, "Input string too long or not null-terminated\n");
        return EXIT_FAILURE;
    }

    if (len > SIZE_MAX - 1) {
        fprintf(stderr, "Length overflow\n");
        return EXIT_FAILURE;
    }

    buffer_size = len + 1;
    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (snprintf(buffer, buffer_size, "%s", source) < 0) {
        fprintf(stderr, "Copy failed\n");
        free(buffer);
        return EXIT_FAILURE;
    }

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