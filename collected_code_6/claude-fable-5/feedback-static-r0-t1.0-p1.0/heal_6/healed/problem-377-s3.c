#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

void remove_char(char *str, char c)
{
    size_t read_idx = 0;
    size_t write_idx = 0;

    if (str == NULL) {
        return;
    }

    while (str[read_idx] != '\0') {
        if (str[read_idx] != c) {
            str[write_idx] = str[read_idx];
            write_idx++;
        }
        read_idx++;
    }
    str[write_idx] = '\0';
}

int main(void)
{
    const char *source = "hello world, hello everyone";
    char target = 'l';
    char *buffer = NULL;
    size_t source_len;
    size_t buffer_size;
    int written;

    source_len = strnlen(source, BUFFER_SIZE);
    if (source_len >= BUFFER_SIZE) {
        fprintf(stderr, "Source string too long\n");
        return EXIT_FAILURE;
    }

    buffer_size = source_len + 1;
    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    written = snprintf(buffer, buffer_size, "%s", source);
    if (written < 0 || (size_t)written >= buffer_size) {
        fprintf(stderr, "Failed to copy source string safely\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Original string: %s\n", buffer);
    remove_char(buffer, target);
    printf("After removing '%c': %s\n", target, buffer);

    free(buffer);
    return EXIT_SUCCESS;
}