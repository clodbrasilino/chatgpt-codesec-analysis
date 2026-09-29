#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int starts_and_ends_with_same_character(const char *string,
                                                size_t length,
                                                int *result)
{
    if (string == NULL || result == NULL) {
        return -1;
    }

    *result = length > 0 && string[0] == string[length - 1];
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t bytes_read;
    size_t length;
    int result;

    bytes_read = getline(&input, &capacity, stdin);
    if (bytes_read < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    length = (size_t)bytes_read;

    while (length > 0 &&
           (input[length - 1] == '\n' || input[length - 1] == '\r')) {
        --length;
    }

    if (starts_and_ends_with_same_character(input, length, &result) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    puts(result ? "Yes" : "No");

    free(input);
    return EXIT_SUCCESS;
}