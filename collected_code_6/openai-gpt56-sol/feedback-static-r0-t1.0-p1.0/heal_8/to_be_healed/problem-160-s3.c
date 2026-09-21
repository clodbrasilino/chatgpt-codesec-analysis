#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    old_r = (__int128)a;
    r = (__int128)b;
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

    if (old_r > (__int128)UINT64_MAX ||
        old_s < (__int128)INT64_MIN ||
        old_s > (__int128)INT64_MAX ||
        old_t < (__int128)INT64_MIN ||
        old_t > (__int128)INT64_MAX) {
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

    if (result_x < (__int128)INT64_MIN ||
        result_x > (__int128)INT64_MAX ||
        result_y < (__int128)INT64_MIN ||
        result_y > (__int128)INT64_MAX) {
        return 0;
    }

    *x = (int64_t)result_x;
    *y = (int64_t)result_y;
    return 1;
}

static int is_space_character(char c)
{
    return c == ' ' || c == '\t' || c == '\n' ||
           c == '\r' || c == '\f' || c == '\v';
}

static int parse_int64(const char **input, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return 0;
    }

    while (is_space_character(**input)) {
        ++*input;
    }

    if (**input == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(*input, &end, 10);

    if (end == *input ||
        errno == ERANGE ||
        parsed < (intmax_t)INT64_MIN ||
        parsed > (intmax_t)INT64_MAX) {
        return 0;
    }

    *input = end;
    *value = (int64_t)parsed;
    return 1;
}

static int discard_line(void)
{
    int c;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(stdin);
    } while (c != '\n' && c != EOF);

    return c == '\n' || feof(stdin);
}

static int read_line(char **line)
{
    enum { MAX_INPUT_LENGTH = 4096 };
    char *buffer;
    size_t capacity = (size_t)MAX_INPUT_LENGTH + 2U;
    size_t length;
    int next;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        free(buffer);
        return 0;
    }

    length = strnlen(buffer, capacity);

    if (length == capacity) {
        discard_line();
        free(buffer);
        return 0;
    }

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
    } else if (length > (size_t)MAX_INPUT_LENGTH) {
        discard_line();
        free(buffer);
        return 0;
    } else {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        next = fgetc(stdin);

        if (next != '\n' && next != EOF) {
            discard_line();
            free(buffer);
            return 0;
        }

        if (next == EOF && ferror(stdin)) {
            free(buffer);
            return 0;
        }
    }

    *line = buffer;
    return 1;
}

int main(void)
{
    char *input;
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