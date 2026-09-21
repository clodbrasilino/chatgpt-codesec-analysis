#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t sum;

    if (result == NULL || n == UINT64_MAX) {
        return 0;
    }

    a = n;
    b = n + UINT64_C(1);

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return 0;
    }

    sum = a * b;

    if (sum != 0 && sum > UINT64_MAX / sum) {
        return 0;
    }

    *result = sum * sum - sum;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t position = 0;
    uint64_t number = 0;
    int ch;
    int success = 0;

    if (value == NULL) {
        return 0;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *new_line;
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            goto cleanup;
        }

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                goto cleanup;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        goto cleanup;
    }

    if (length + 1 >= capacity) {
        char *new_line;
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            goto cleanup;
        }

        new_capacity = length + 1;
        new_line = realloc(line, new_capacity);
        if (new_line == NULL) {
            goto cleanup;
        }

        line = new_line;
        capacity = new_capacity;
    }

    line[length] = '\0';

    while (line[position] == ' ' || line[position] == '\t' ||
           line[position] == '\r' || line[position] == '\f' ||
           line[position] == '\v') {
        ++position;
    }

    if (line[position] == '\0' ||
        line[position] == '+' ||
        line[position] == '-') {
        goto cleanup;
    }

    while (line[position] >= '0' && line[position] <= '9') {
        uint64_t digit = (uint64_t)(line[position] - '0');

        if (number > (UINT64_MAX - digit) / UINT64_C(10)) {
            goto cleanup;
        }

        number = number * UINT64_C(10) + digit;
        ++position;
    }

    while (line[position] == ' ' || line[position] == '\t' ||
           line[position] == '\r' || line[position] == '\f' ||
           line[position] == '\v') {
        ++position;
    }

    if (line[position] != '\0') {
        goto cleanup;
    }

    *value = number;
    success = 1;

cleanup:
    free(line);
    return success;
}

int main(void)
{
    uint64_t n;
    uint64_t difference;

    if (!read_uint64(&n)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_difference(n, &difference)) {
        fputs("Result is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}