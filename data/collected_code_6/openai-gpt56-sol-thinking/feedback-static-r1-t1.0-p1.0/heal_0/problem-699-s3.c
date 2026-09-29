#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int minimum_swaps(const char *source, const char *target, size_t *result)
{
    size_t zero_to_one = 0;
    size_t one_to_zero = 0;
    size_t i = 0;

    if (source == NULL || target == NULL || result == NULL) {
        return -1;
    }

    while (source[i] != '\0' && target[i] != '\0') {
        if ((source[i] != '0' && source[i] != '1') ||
            (target[i] != '0' && target[i] != '1')) {
            return -1;
        }

        if (source[i] == '0' && target[i] == '1') {
            ++zero_to_one;
        } else if (source[i] == '1' && target[i] == '0') {
            ++one_to_zero;
        }

        ++i;
    }

    if (source[i] != '\0' || target[i] != '\0') {
        return 1;
    }

    if (zero_to_one != one_to_zero) {
        return 1;
    }

    *result = zero_to_one;
    return 0;
}

static int read_token(FILE *stream, char **output)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer;
    int ch;

    if (stream == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    do {
        ch = fgetc(stream);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        free(buffer);
        return ferror(stream) ? -1 : 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        ch = fgetc(stream);
    }

    if (ch == EOF && ferror(stream)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *output = buffer;
    return 1;
}

int main(void)
{
    char *source = NULL;
    char *target = NULL;
    size_t swaps = 0;
    int read_status;
    int status;
    int exit_status = EXIT_FAILURE;

    read_status = read_token(stdin, &source);
    if (read_status != 1) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    read_status = read_token(stdin, &target);
    if (read_status != 1) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    status = minimum_swaps(source, target, &swaps);
    if (status < 0) {
        fputs("Invalid binary string\n", stderr);
        goto cleanup;
    }

    if (status > 0) {
        puts("-1");
    } else {
        printf("%zu\n", swaps);
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(target);
    free(source);
    return exit_status;
}