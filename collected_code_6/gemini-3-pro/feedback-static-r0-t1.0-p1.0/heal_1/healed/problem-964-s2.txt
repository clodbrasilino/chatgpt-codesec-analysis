#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_even_length(const char *word) {
    if (word == NULL) {
        return false;
    }

    size_t length = 0;
    while (word[length] != '\0') {
        length++;
    }

    return (length % 2 == 0);
}

int main(void) {
    char *input = NULL;
    size_t buf_size = 0;
    ssize_t read_bytes;

    read_bytes = getline(&input, &buf_size, stdin);

    if (read_bytes != -1) {
        if (read_bytes > 0 && input[read_bytes - 1] == '\n') {
            input[read_bytes - 1] = '\0';
        }

        if (is_even_length(input)) {
            printf("Even\n");
        } else {
            printf("Odd\n");
        }
    }

    free(input);
    return EXIT_SUCCESS;
}