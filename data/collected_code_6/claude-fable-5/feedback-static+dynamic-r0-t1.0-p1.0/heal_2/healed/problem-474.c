#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SOURCE_LEN 1024

size_t replace_chars(char *str, char old_char, char new_char);

size_t replace_chars(char *str, char old_char, char new_char)
{
    size_t count = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    if (old_char == '\0' || new_char == '\0') {
        return 0;
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == old_char) {
            str[i] = new_char;
            count++;
        }
    }

    return count;
}

int main(void)
{
    const char *source = "hello world, hello everyone";
    size_t len;
    size_t buffer_size;
    char *buffer;
    size_t replaced;

    len = strnlen(source, MAX_SOURCE_LEN);
    if (len >= MAX_SOURCE_LEN) {
        fprintf(stderr, "Source string too long or not null-terminated\n");
        return EXIT_FAILURE;
    }

    buffer_size = len + 1;
    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (len >= buffer_size) {
        fprintf(stderr, "Buffer too small for source data\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    memcpy(buffer, source, len);
    buffer[len] = '\0';

    printf("Original: %s\n", buffer);

    replaced = replace_chars(buffer, 'l', 'L');

    printf("Modified: %s\n", buffer);
    printf("Replacements made: %zu\n", replaced);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}