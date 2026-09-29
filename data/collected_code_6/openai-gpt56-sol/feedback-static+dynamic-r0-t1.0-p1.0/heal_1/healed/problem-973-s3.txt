#define _POSIX_C_SOURCE 200809L

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void reverse_range(char *string, size_t begin, size_t end)
{
    while (begin < end) {
        char temporary = string[begin];
        string[begin++] = string[end];
        string[end--] = temporary;
    }
}

static int left_rotate_string(char *string, size_t length,
                              unsigned long long positions)
{
    size_t rotation;

    if (string == NULL) {
        return -1;
    }

    if (length == 0U) {
        return 0;
    }

    rotation = (size_t)(positions % (unsigned long long)length);
    if (rotation == 0U) {
        return 0;
    }

    reverse_range(string, 0U, rotation - 1U);
    reverse_range(string, rotation, length - 1U);
    reverse_range(string, 0U, length - 1U);

    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0U;
    size_t string_length;
    ssize_t input_length;
    unsigned long long positions;
    int extra;
    int result = EXIT_FAILURE;

    input_length = getline(&line, &capacity, stdin);
    if (input_length < 0) {
        goto cleanup;
    }

    string_length = (size_t)input_length;

    if (string_length > 0U && line[string_length - 1U] == '\n') {
        line[--string_length] = '\0';

        if (string_length > 0U && line[string_length - 1U] == '\r') {
            line[--string_length] = '\0';
        }
    }

    if (scanf("%llu", &positions) != 1) {
        goto cleanup;
    }

    do {
        extra = getchar();
    } while (extra == ' ' || extra == '\t' || extra == '\r');

    if (extra != '\n' && extra != EOF) {
        goto cleanup;
    }

    if (left_rotate_string(line, string_length, positions) != 0) {
        goto cleanup;
    }

    if (puts(line) == EOF) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(line);
    return result;
}