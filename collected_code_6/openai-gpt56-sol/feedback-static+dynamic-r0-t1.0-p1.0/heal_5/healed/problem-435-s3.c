#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t last_digit(intmax_t number)
{
    uintmax_t magnitude;

    if (number < 0) {
        magnitude = (uintmax_t)(-(number + 1)) + UINTMAX_C(1);
    } else {
        magnitude = (uintmax_t)number;
    }

    return magnitude % UINTMAX_C(10);
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *start;
    char *end;
    intmax_t number;
    int character;
    int status = EXIT_FAILURE;

    for (;;) {
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            goto cleanup;
        }

        if (capacity < length + 2) {
            size_t required = length + 2;
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 64;
            } else if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && (ferror(stdin) || length == 0)) {
        goto cleanup;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            goto cleanup;
        }
    }

    input[length] = '\0';
    start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    number = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE) {
        goto cleanup;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    if (printf("%" PRIuMAX "\n", last_digit(number)) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}