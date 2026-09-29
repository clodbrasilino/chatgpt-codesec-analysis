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

static char *duplicate_string(const char *src, size_t max_len)
{
    size_t len;
    char *dest;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, max_len);
    if (len >= max_len) {
        return NULL;
    }

    dest = malloc(len + 1);
    if (dest == NULL) {
        return NULL;
    }

    size_t i;
    for (i = 0; i < len && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';

    return dest;
}

int main(void)
{
    static const char source[] = "Hello, World! 123 abc";
    char *buffer;

    buffer = duplicate_string(source, MAX_INPUT_LEN);
    if (buffer == NULL) {
        fprintf(stderr, "Failed to duplicate input string\n");
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