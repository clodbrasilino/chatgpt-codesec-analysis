#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_multiple_spaces(char *str)
{
    size_t read_idx = 0;
    size_t write_idx = 0;
    int prev_space = 0;

    if (str == NULL) {
        return;
    }

    while (str[read_idx] != '\0') {
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
    str[write_idx] = '\0';
}

int main(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t nread;
    size_t len;

    if (printf("Enter a string: ") < 0) {
        fprintf(stderr, "Error writing output\n");
        return 1;
    }

    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error flushing output\n");
        return 1;
    }

    nread = getline(&buffer, &bufsize, stdin);
    if (nread < 0) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }

    len = (size_t)nread;
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    remove_multiple_spaces(buffer);

    if (printf("Result: %s\n", buffer) < 0) {
        fprintf(stderr, "Error writing output\n");
        free(buffer);
        return 1;
    }

    free(buffer);
    return 0;
}