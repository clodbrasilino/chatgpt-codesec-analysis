#define _POSIX_C_SOURCE 200809L

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static int count_odd_rotations(const char *binary)
{
    size_t length;
    size_t count = 0;

    if (binary == NULL) {
        return -1;
    }

    length = strlen(binary);

    for (size_t i = 0; i < length; ++i) {
        if (binary[i] != '0' && binary[i] != '1') {
            return -1;
        }

        if (binary[i] == '1') {
            ++count;
        }
    }

    if (count > (size_t)INT_MAX) {
        return -1;
    }

    return (int)count;
}

int main(void)
{
    char *binary = NULL;
    size_t capacity = 0;
    ssize_t length;
    int result;

    length = getline(&binary, &capacity, stdin);
    if (length < 0) {
        free(binary);
        return EXIT_FAILURE;
    }

    while (length > 0 &&
           (binary[length - 1] == '\n' || binary[length - 1] == '\r')) {
        binary[--length] = '\0';
    }

    result = count_odd_rotations(binary);
    free(binary);

    if (result < 0) {
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}