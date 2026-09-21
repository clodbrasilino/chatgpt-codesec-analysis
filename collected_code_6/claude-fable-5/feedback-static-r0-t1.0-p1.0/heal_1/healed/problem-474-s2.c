#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 1024

size_t replace_char(char *str, size_t max_len, char old_char, char new_char)
{
    size_t count = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; i < max_len && str[i] != '\0'; i++) {
        if (str[i] == old_char) {
            str[i] = new_char;
            count++;
        }
    }

    return count;
}

int main(void)
{
    static const char original[] = "hello world, hello everyone";
    size_t len;
    char *buffer;
    size_t replaced;

    len = strnlen(original, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        fprintf(stderr, "Input string too long or not terminated\n");
        return EXIT_FAILURE;
    }

    buffer = malloc(len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(buffer, original, len);
    buffer[len] = '\0';

    replaced = replace_char(buffer, len, 'l', 'L');

    if (printf("Original: %s\n", original) < 0) {
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