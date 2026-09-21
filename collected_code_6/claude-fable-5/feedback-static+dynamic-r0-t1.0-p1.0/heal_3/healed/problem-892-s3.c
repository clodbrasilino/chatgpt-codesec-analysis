#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

void remove_multiple_spaces(char *str)
{
    size_t read_idx;
    size_t write_idx;
    int prev_space;

    if (str == NULL) {
        return;
    }

    read_idx = 0;
    write_idx = 0;
    prev_space = 0;

    while (str[read_idx] != '\0') {
        if (str[read_idx] == ' ') {
            if (!prev_space) {
                str[write_idx] = str[read_idx];
                write_idx++;
                prev_space = 1;
            }
        } else {
            str[write_idx] = str[read_idx];
            write_idx++;
            prev_space = 0;
        }
        read_idx++;
    }

    str[write_idx] = '\0';
}

int main(void)
{
    static const char test[] = "This   is  a    string   with  multiple    spaces";
    char *buffer;
    size_t test_len;
    size_t buffer_size;
    int written;

    test_len = strnlen(test, sizeof(test));

    if (test_len >= BUFFER_SIZE) {
        fprintf(stderr, "Input string too long\n");
        return EXIT_FAILURE;
    }

    buffer_size = test_len + 1;
    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    written = snprintf(buffer, buffer_size, "%s", test);
    if (written < 0 || (size_t)written >= buffer_size) {
        fprintf(stderr, "Failed to copy input string\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Before: \"%s\"\n", buffer);

    remove_multiple_spaces(buffer);

    printf("After:  \"%s\"\n", buffer);

    free(buffer);

    return EXIT_SUCCESS;
}