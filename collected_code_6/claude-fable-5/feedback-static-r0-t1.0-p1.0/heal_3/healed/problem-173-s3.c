#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void remove_non_alnum(char *str)
{
    size_t read_idx;
    size_t write_idx;

    if (str == NULL) {
        return;
    }

    read_idx = 0;
    write_idx = 0;

    while (str[read_idx] != '\0') {
        if (isalnum((unsigned char)str[read_idx])) {
            str[write_idx] = str[read_idx];
            write_idx++;
        }
        read_idx++;
    }

    str[write_idx] = '\0';
}

int main(void)
{
    const char *input = "Hello, World! 123 #$% foo_bar";
    size_t input_len;
    char *buffer;
    int written;

    input_len = strlen(input);

    buffer = malloc(input_len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    written = snprintf(buffer, input_len + 1, "%s", input);
    if (written < 0 || (size_t)written > input_len) {
        fprintf(stderr, "Input too long or encoding error\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Before: %s\n", buffer);

    remove_non_alnum(buffer);

    printf("After:  %s\n", buffer);

    free(buffer);

    return EXIT_SUCCESS;
}