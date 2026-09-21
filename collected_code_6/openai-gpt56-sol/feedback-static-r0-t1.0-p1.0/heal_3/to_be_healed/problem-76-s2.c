#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int checked_add_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || a > UINT64_MAX - b) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int checked_mul_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || (a != 0 && b > UINT64_MAX / a)) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static int triangular_u64(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;

    if (result == NULL || n == UINT64_MAX) {
        return 0;
    }

    a = n;
    b = n + 1;

    if ((a & UINT64_C(1)) == 0) {
        a /= 2;
    } else {
        b /= 2;
    }

    return checked_mul_u64(a, b, result);
}

static int sum_squares_u64(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t product;

    if (result == NULL || n == UINT64_MAX ||
        n > (UINT64_MAX - UINT64_C(1)) / UINT64_C(2)) {
        return 0;
    }

    a = n;
    b = n + 1;
    c = 2 * n + 1;

    if ((a & UINT64_C(1)) == 0) {
        a /= 2;
    } else {
        b /= 2;
    }

    if (a % 3 == 0) {
        a /= 3;
    } else if (b % 3 == 0) {
        b /= 3;
    } else {
        c /= 3;
    }

    if (!checked_mul_u64(a, b, &product)) {
        return 0;
    }

    return checked_mul_u64(product, c, result);
}

static int count_squares(uint64_t width, uint64_t height, uint64_t *result)
{
    uint64_t side;
    uint64_t other;
    uint64_t triangular;
    uint64_t square_sum;
    uint64_t factor;
    uint64_t product;

    if (result == NULL || width == 0 || height == 0) {
        return 0;
    }

    if (width < height) {
        side = width;
        other = height;
    } else {
        side = height;
        other = width;
    }

    if (!checked_add_u64(other, UINT64_C(1), &factor) ||
        !triangular_u64(side, &triangular) ||
        !sum_squares_u64(side, &square_sum) ||
        !checked_mul_u64(factor, triangular, &product) ||
        square_sum > product) {
        return 0;
    }

    *result = product - square_sum;
    return 1;
}

static int parse_u64(const char **cursor, uint64_t *value)
{
    const char *p;
    char *end;
    uintmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    p = *cursor;
    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p == '\0' || *p == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(p, &end, 10);

    if (p == end || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *cursor = end;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    const char *cursor;
    uint64_t width;
    uint64_t height;
    uint64_t result;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        char *resized;

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    fputs("Invalid input\n", stderr);
                    return 1;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Memory allocation failure\n", stderr);
                return 1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (length + 1 >= capacity) {
        char *resized;
        size_t new_capacity = capacity == 0 ? 1 : capacity + 1;

        resized = realloc(input, new_capacity);
        if (resized == NULL) {
            free(input);
            fputs("Memory allocation failure\n", stderr);
            return 1;
        }

        input = resized;
        /* Possible weaknesses found:
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity = new_capacity;
    }

    input[length] = '\0';
    cursor = input;

    if (!parse_u64(&cursor, &width) || !parse_u64(&cursor, &height)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return 1;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return 1;
    }

    free(input);

    if (!count_squares(width, height, &result)) {
        fputs("Invalid dimensions or arithmetic overflow\n", stderr);
        return 1;
    }

    printf("%" PRIu64 "\n", result);
    return 0;
}