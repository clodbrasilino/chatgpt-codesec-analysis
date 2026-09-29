#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void remove_multiple_spaces(char *str, size_t max_len)
{
    size_t read_idx = 0;
    size_t write_idx = 0;
    int prev_space = 0;

    if (str == NULL || max_len == 0) {
        return;
    }

    while (read_idx < max_len && str[read_idx] != '\0') {
        if (str[read_idx] == ' ') {
            if (!prev_space) {
                str[write_idx] = str[read_idx];
                write_idx++;
            }
            prev_space = 1;
        } else {
            str[write_idx] = str[read_idx];
            write_idx++;
            prev_space = 0;
        }
        read_idx++;
    }

    if (write_idx >= max_len) {
        write_idx = max_len - 1;
    }
    str[write_idx] = '\0';
}

int main(void)
{
    char *buffer;
    size_t len;

    buffer = calloc(BUFFER_SIZE, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter a string: ");
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }

    buffer[BUFFER_SIZE - 1] = '\0';

    len = strnlen(buffer, BUFFER_SIZE);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    remove_multiple_spaces(buffer, BUFFER_SIZE);

    if (printf("Result: %s\n", buffer) < 0) {
        fprintf(stderr, "Error writing output\n");
        free(buffer);
        return 1;
    }

    free(buffer);
    return 0;
}