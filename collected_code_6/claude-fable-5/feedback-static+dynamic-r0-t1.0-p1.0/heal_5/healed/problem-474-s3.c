#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 256

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
    char *buffer;
    size_t len;
    size_t buffer_size;
    size_t replaced;
    int written;

    len = strnlen(original, MAX_INPUT_LEN);
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

    written = snprintf(buffer, buffer_size, "%s", original);
    if (written < 0 || (size_t)written >= buffer_size) {
        fprintf(stderr, "Failed to copy string safely\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Before: %s\n", buffer);

    replaced = replace_char(buffer, buffer_size, 'l', 'L');

    printf("After:  %s\n", buffer);
    printf("Replaced %zu occurrence(s)\n", replaced);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}