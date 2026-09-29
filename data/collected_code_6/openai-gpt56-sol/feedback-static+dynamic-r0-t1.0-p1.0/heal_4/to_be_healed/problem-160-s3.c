#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int extended_gcd(int64_t a, int64_t b, int64_t *x, int64_t *y,
                        uint64_t *gcd)
{
    __int128 old_r;
    __int128 r;
    __int128 old_s;
    __int128 s;
    __int128 old_t;
    __int128 t;

    if (x == NULL || y == NULL || gcd == NULL) {
        return 0;
    }

    old_r = a;
    r = b;
    old_s = 1;
    s = 0;
    old_t = 0;
    t = 1;

    while (r != 0) {
        __int128 quotient = old_r / r;
        __int128 next_r = old_r - quotient * r;
        __int128 next_s = old_s - quotient * s;
        __int128 next_t = old_t - quotient * t;

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

    if (old_r > UINT64_MAX ||
        old_s < INT64_MIN || old_s > INT64_MAX ||
        old_t < INT64_MIN || old_t > INT64_MAX) {
        return 0;
    }

    *gcd = (uint64_t)old_r;
    *x = (int64_t)old_s;
    *y = (int64_t)old_t;

    return 1;
}

static int find_solution(int64_t a, int64_t b, int64_t n,
                         int64_t *x, int64_t *y)
{
    int64_t base_x;
    int64_t base_y;
    uint64_t gcd;
    __int128 multiplier;
    __int128 result_x;
    __int128 result_y;

    if (x == NULL || y == NULL) {
        return 0;
    }

    if (a == 0 && b == 0) {
        if (n != 0) {
            return 0;
        }

        *x = 0;
        *y = 0;
        return 1;
    }

    if (!extended_gcd(a, b, &base_x, &base_y, &gcd) || gcd == 0) {
        return 0;
    }

    if ((__int128)n % (__int128)gcd != 0) {
        return 0;
    }

    multiplier = (__int128)n / (__int128)gcd;
    result_x = (__int128)base_x * multiplier;
    result_y = (__int128)base_y * multiplier;

    if (result_x < INT64_MIN || result_x > INT64_MAX ||
        result_y < INT64_MIN || result_y > INT64_MAX) {
        return 0;
    }

    *x = (int64_t)result_x;
    *y = (int64_t)result_y;

    return 1;
}

static int is_space_character(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int parse_int64(const char **cursor, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    while (is_space_character(**cursor)) {
        ++*cursor;
    }

    if (**cursor == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    *cursor = end;

    return 1;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 64;
    char *buffer;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;

    return 1;
}

int main(void)
{
    char *input = NULL;
    const char *cursor;
    int64_t a;
    int64_t b;
    int64_t n;
    int64_t x;
    int64_t y;

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_int64(&cursor, &a) ||
        !parse_int64(&cursor, &b) ||
        !parse_int64(&cursor, &n)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (is_space_character(*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!find_solution(a, b, n, &x, &y)) {
        puts("No representable integer solution");
        return EXIT_SUCCESS;
    }

    printf("x = %" PRId64 ", y = %" PRId64 "\n", x, y);

    return EXIT_SUCCESS;
}