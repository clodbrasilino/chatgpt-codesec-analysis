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
        char *resized;
        size_t new_capacity;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
        if (character == '\n' || character == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            goto cleanup;
        }

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    goto cleanup;
                }
                new_capacity = capacity * 2;
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

    if (capacity <= length) {
        char *resized;

        if (length == SIZE_MAX) {
            goto cleanup;
        }

        resized = realloc(input, length + 1);
        if (resized == NULL) {
            goto cleanup;
        }

        input = resized;
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