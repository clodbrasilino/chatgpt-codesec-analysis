#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    return a >= modulus - b ? a - (modulus - b) : a + b;
}

static uint64_t ncr_mod(uint64_t n, uint64_t r, uint64_t modulus, int *error)
{
    uint64_t *row;
    uint64_t result;
    size_t count;

    *error = 0;

    if (modulus == 1 || r > n) {
        return 0;
    }

    if (r > n - r) {
        r = n - r;
    }

    if (r > (uint64_t)(SIZE_MAX / sizeof(*row) - 1U)) {
        *error = ENOMEM;
        return 0;
    }

    count = (size_t)r + 1U;
    row = calloc(count, sizeof(*row));
    if (row == NULL) {
        *error = ENOMEM;
        return 0;
    }

    row[0] = 1U % modulus;

    for (uint64_t i = 1; i <= n; ++i) {
        uint64_t limit = i < r ? i : r;

        for (uint64_t j = limit; j > 0; --j) {
            row[j] = add_mod(row[j], row[j - 1U], modulus);
        }

        if (i == UINT64_MAX) {
            break;
        }
    }

    result = row[r];
    free(row);
    return result;
}

static int is_space_char(unsigned char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int parse_uint64(const char **cursor, uint64_t *value)
{
    const unsigned char *p = (const unsigned char *)*cursor;
    uint64_t result = 0;

    while (is_space_char(*p)) {
        ++p;
    }

    if (*p < '0' || *p > '9') {
        return 0;
    }

    do {
        unsigned int digit = (unsigned int)(*p - '0');

        if (result > (UINT64_MAX - digit) / 10U) {
            return 0;
        }

        result = result * 10U + digit;
        ++p;
    } while (*p >= '0' && *p <= '9');

    if (*p != '\0' && !is_space_char(*p)) {
        return 0;
    }

    *cursor = (const char *)p;
    *value = result;
    return 1;
}

static char *read_all_input(void)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (length == SIZE_MAX - 1U) {
            free(buffer);
            errno = ENOMEM;
            return NULL;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity == 0) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(buffer);
                    errno = ENOMEM;
                    return NULL;
                }
                new_capacity = capacity * 2U;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                errno = ENOMEM;
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (length + 1U > capacity) {
        char *new_buffer = realloc(buffer, length + 1U);

        if (new_buffer == NULL) {
            free(buffer);
            errno = ENOMEM;
            return NULL;
        }

        buffer = new_buffer;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    const char *cursor;
    uint64_t values[3];
    uint64_t result;
    int error;

    errno = 0;
    input = read_all_input();
    if (input == NULL) {
        fputs(errno == ENOMEM ? "Memory allocation failed\n" : "Invalid input\n",
              stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    for (size_t i = 0; i < 3U; ++i) {
        if (!parse_uint64(&cursor, &values[i])) {
            free(input);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    while (is_space_char((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (values[2] == 0) {
        fputs("Modulus must be nonzero\n", stderr);
        return EXIT_FAILURE;
    }

    result = ncr_mod(values[0], values[1], values[2], &error);
    if (error != 0) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}