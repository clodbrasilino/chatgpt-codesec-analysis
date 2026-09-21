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
    char *start;
    char *end;
    size_t capacity = 0;
    size_t length = 0;
    intmax_t number;
    int character;
    int status = EXIT_FAILURE;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            goto cleanup;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    new_capacity = SIZE_MAX;
                } else {
                    new_capacity = capacity * 2;
                }
            }

            if (new_capacity <= length + 1) {
                goto cleanup;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (character == EOF) {
        if (ferror(stdin) || length == 0) {
            goto cleanup;
        }
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'input==NULL' is not redundant
     */
    if (input == NULL || capacity <= length) {
        char *resized;

        if (length == SIZE_MAX) {
            goto cleanup;
        }

        resized = realloc(input, length + 1);
        if (resized == NULL) {
            goto cleanup;
        }

        input = resized;
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity = length + 1;
    }

    /* Possible weaknesses found:
     *  Null pointer dereference
     *  Either the condition 'input==NULL' is redundant or there is possible null pointer dereference: input. [nullPointerRedundantCheck]
     */
    input[length] = '\0';

    /* Possible weaknesses found:
     *  Assignment 'start=input', assigned value is 0
     */
    start = input;
    /* Possible weaknesses found:
     *  Either the condition 'input==NULL' is redundant or there is possible null pointer dereference: start. [nullPointerRedundantCheck]
     *  Null pointer dereference
     */
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    number = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE) {
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
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