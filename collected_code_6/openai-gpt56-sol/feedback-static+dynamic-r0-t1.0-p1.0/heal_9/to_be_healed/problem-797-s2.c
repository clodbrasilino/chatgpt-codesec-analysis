#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_odd_naturals(uint64_t left, uint64_t right, uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t factor;

    if (result == NULL || left == 0 || left > right) {
        return 0;
    }

    first = left | UINT64_C(1);
    last = (right & UINT64_C(1)) != 0
        ? right
        : right - UINT64_C(1);

    if (first > last) {
        *result = 0;
        return 1;
    }

    count = (last - first) / UINT64_C(2) + UINT64_C(1);
    factor = first + count - UINT64_C(1);

    if (count != 0 && factor > UINT64_MAX / count) {
        return 0;
    }

    *result = count * factor;
    return 1;
}

static char *read_line(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);
    int ch;

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

static int parse_input(const char *input, uint64_t *left, uint64_t *right)
{
    const unsigned char *cursor;
    uint64_t values[2];
    size_t index;

    if (input == NULL || left == NULL || right == NULL) {
        return 0;
    }

    cursor = (const unsigned char *)input;

    for (index = 0; index < 2; ++index) {
        uint64_t value = 0;
        int digit_seen = 0;

        while (*cursor != '\0' && isspace(*cursor)) {
            ++cursor;
        }

        if (*cursor == '+' || *cursor == '-') {
            return 0;
        }

        while (*cursor != '\0' && isdigit(*cursor)) {
            unsigned int digit = (unsigned int)(*cursor - '0');

            digit_seen = 1;

            if (value > (UINT64_MAX - digit) / UINT64_C(10)) {
                return 0;
            }

            value = value * UINT64_C(10) + digit;
            ++cursor;
        }

        if (!digit_seen) {
            return 0;
        }

        if (*cursor != '\0' && !isspace(*cursor)) {
            return 0;
        }

        values[index] = value;
    }

    while (*cursor != '\0' && isspace(*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        return 0;
    }

    *left = values[0];
    *right = values[1];
    return 1;
}

int main(void)
{
    char *input;
    uint64_t left;
    uint64_t right;
    uint64_t sum;

    input = read_line();
    if (input == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!parse_input(input, &left, &right)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!sum_odd_naturals(left, right, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}