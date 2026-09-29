#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    len = strnlen(original, sizeof(original));
    if (len >= sizeof(original)) {
        fprintf(stderr, "Source string is not properly terminated\n");
        return EXIT_FAILURE;
    }

    buffer_size = len + 1;
    if (buffer_size < len) {
        fprintf(stderr, "Buffer size calculation overflow\n");
        return EXIT_FAILURE;
    }

    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (len >= buffer_size) {
        fprintf(stderr, "Destination buffer too small\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    memcpy(buffer, original, len);
    buffer[len] = '\0';

    printf("Before: %s\n", buffer);

    replaced = replace_char(buffer, buffer_size, 'l', 'L');

    printf("After:  %s\n", buffer);
    printf("Replaced %zu occurrence(s)\n", replaced);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}