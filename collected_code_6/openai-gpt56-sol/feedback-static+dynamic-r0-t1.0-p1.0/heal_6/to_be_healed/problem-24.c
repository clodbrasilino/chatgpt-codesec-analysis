#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UINTMAX_BINARY_DIGITS (sizeof(uintmax_t) * 8U)
#define BINARY_BUFFER_SIZE (UINTMAX_BINARY_DIGITS + 2U)

static int binary_to_decimal(const char *binary, uintmax_t *decimal)
{
    uintmax_t value = 0;

    if (binary == NULL || decimal == NULL || *binary == '\0') {
        return -1;
    }

    for (const unsigned char *p = (const unsigned char *)binary;
         *p != '\0';
         ++p) {
        unsigned int digit;

        if (*p == (unsigned char)'0') {
            digit = 0U;
        } else if (*p == (unsigned char)'1') {
            digit = 1U;
        } else {
            return -1;
        }

        if (value > (UINTMAX_MAX - digit) / 2U) {
            return -1;
        }

        value = value * 2U + digit;
    }

    *decimal = value;
    return 0;
}

static int read_binary_line(char **line)
{
    size_t length = 0;
    size_t capacity = 16;
    char *buffer;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stdin)) {
                free(buffer);
                return -1;
            }

            if (length == 0U) {
                free(buffer);
                return -1;
            }

            buffer[length] = '\0';
            *line = buffer;
            return 0;
        }

        if (length >= UINTMAX_BINARY_DIGITS) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            free(buffer);
            return -1;
        }

        if (ch != '0' && ch != '1') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            free(buffer);
            return -1;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity >= UINTMAX_BINARY_DIGITS + 1U) {
                new_capacity = UINTMAX_BINARY_DIGITS + 1U;
            } else if (capacity > (UINTMAX_BINARY_DIGITS + 1U) / 2U) {
                new_capacity = UINTMAX_BINARY_DIGITS + 1U;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return -1;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }
}

int main(void)
{
    char *binary = NULL;
    uintmax_t decimal;

    if (read_binary_line(&binary) != 0) {
        return EXIT_FAILURE;
    }

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