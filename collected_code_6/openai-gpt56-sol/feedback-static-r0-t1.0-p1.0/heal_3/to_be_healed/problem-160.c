#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int extended_gcd(int64_t a, int64_t b, int64_t *x, int64_t *y,
                        int64_t *gcd)
{
    if (x == NULL || y == NULL || gcd == NULL) {
        return 0;
    }

    __int128 old_r = a;
    __int128 r = b;
    __int128 old_s = 1;
    __int128 s = 0;
    __int128 old_t = 0;
    __int128 t = 1;

    while (r != 0) {
        __int128 q = old_r / r;
        __int128 next_r = old_r - q * r;
        __int128 next_s = old_s - q * s;
        __int128 next_t = old_t - q * t;

        old_r = r;
        r = next_r;
        old_s = s;
        s = next_s;
        old_t = t;
        t = next_t;
    }

    if (old_r < 0) {
        old_r = -old_r;
        old_s = -old_s;
        old_t = -old_t;
    }

    if (old_r > INT64_MAX ||
        old_s < INT64_MIN || old_s > INT64_MAX ||
        old_t < INT64_MIN || old_t > INT64_MAX) {
        return 0;
    }

    *gcd = (int64_t)old_r;
    *x = (int64_t)old_s;
    *y = (int64_t)old_t;
    return 1;
}

static int solve_diophantine(int64_t a, int64_t b, int64_t n,
                             int64_t *x, int64_t *y)
{
    if (x == NULL || y == NULL || (a == 0 && b == 0)) {
        return 0;
    }

    int64_t x0;
    int64_t y0;
    int64_t gcd;

    if (!extended_gcd(a, b, &x0, &y0, &gcd) ||
        gcd == 0 || n % gcd != 0) {
        return 0;
    }

    __int128 factor = (__int128)n / gcd;
    __int128 result_x = (__int128)x0 * factor;
    __int128 result_y = (__int128)y0 * factor;

    if (result_x < INT64_MIN || result_x > INT64_MAX ||
        result_y < INT64_MIN || result_y > INT64_MAX) {
        return 0;
    }

    *x = (int64_t)result_x;
    *y = (int64_t)result_y;
    return 1;
}

static int read_line(char **line)
{
    if (line == NULL) {
        return 0;
    }

    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == EOF || ch == '\n') {
            if (ch == EOF && length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int parse_int64(const char **input, int64_t *value)
{
    if (input == NULL || *input == NULL || value == NULL) {
        return 0;
    }

    const char *start = *input;
    char *end = NULL;

    errno = 0;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *input = end;
    *value = (int64_t)parsed;
    return 1;
}

int main(void)
{
    char *input = NULL;

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    const char *cursor = input;
    int64_t a;
    int64_t b;
    int64_t n;
    int64_t x;
    int64_t y;

    if (!parse_int64(&cursor, &a) ||
        !parse_int64(&cursor, &b) ||
        !parse_int64(&cursor, &n)) {
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

    if (!solve_diophantine(a, b, n, &x, &y)) {
        puts("No integer solution");
        return 0;
    }

    printf("x = %" PRId64 ", y = %" PRId64 "\n", x, y);
    return 0;
}