#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int binary_to_decimal(const char *binary, uintmax_t *decimal)
{
    char *end;
    uintmax_t value;

    if (binary == NULL || decimal == NULL || *binary == '\0') {
        return -1;
    }

    errno = 0;
    value = strtoumax(binary, &end, 2);

    if (errno == ERANGE || end == binary || *end != '\0') {
        return -1;
    }

    *decimal = value;
    return 0;
}

int main(void)
{
    char *binary = NULL;
    size_t capacity = 0;
    size_t length = 0;
    uintmax_t decimal;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity;
            char *new_binary;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(binary);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            new_binary = realloc(binary, new_capacity);
            if (new_binary == NULL) {
                free(binary);
                return EXIT_FAILURE;
            }

            binary = new_binary;
            capacity = new_capacity;
        }

        binary[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(binary);
        return EXIT_FAILURE;
    }

    if (length == SIZE_MAX) {
        free(binary);
        return EXIT_FAILURE;
    }

    if (length + 1 > capacity) {
        char *new_binary = realloc(binary, length + 1);

        if (new_binary == NULL) {
            free(binary);
            return EXIT_FAILURE;
        }

        binary = new_binary;
    }

    binary[length] = '\0';

    if (binary_to_decimal(binary, &decimal) != 0) {
        free(binary);
        return EXIT_FAILURE;
    }

    free(binary);

    if (printf("%" PRIuMAX "\n", decimal) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}