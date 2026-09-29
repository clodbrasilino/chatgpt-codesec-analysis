#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

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
    char *buffer;

    len = strlen(source);
    buffer = malloc(len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(buffer, source, len + 1);

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