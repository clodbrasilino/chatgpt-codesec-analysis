#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t magnitude(int64_t value)
{
    if (value >= 0) {
        return (uint64_t)value;
    }

    return (uint64_t)(-(value + 1)) + UINT64_C(1);
}

static uint64_t gcd_extended(uint64_t a, uint64_t b,
                             __int128 *x, __int128 *y)
{
    __int128 old_r = (__int128)a;
    __int128 r = (__int128)b;
    __int128 old_s = 1;
    __int128 s = 0;
    __int128 old_t = 0;
    __int128 t = 1;

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

    *x = old_s;
    *y = old_t;

    return (uint64_t)old_r;
}

static int solve_diophantine(int64_t a, int64_t b, int64_t n,
                             __int128 *x, __int128 *y)
{
    uint64_t gcd;
    __int128 base_x;
    __int128 base_y;
    __int128 factor;

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

    gcd = gcd_extended(magnitude(a), magnitude(b), &base_x, &base_y);

    if ((__int128)n % (__int128)gcd != 0) {
        return 0;
    }

    factor = (__int128)n / (__int128)gcd;
    *x = base_x * factor * (a < 0 ? -1 : 1);
    *y = base_y * factor * (b < 0 ? -1 : 1);

    return 1;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end = NULL;
    intmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int print_int128(__int128 value)
{
    char buffer[64];
    size_t position = sizeof(buffer);
    unsigned __int128 magnitude_value;
    int negative = value < 0;

    magnitude_value = negative
        ? (unsigned __int128)(-(value + 1)) + 1
        : (unsigned __int128)value;

    do {
        unsigned int digit = (unsigned int)(magnitude_value % 10);
        buffer[--position] = (char)('0' + digit);
        magnitude_value /= 10;
    } while (magnitude_value != 0);

    if (negative) {
        buffer[--position] = '-';
    }

    return fwrite(buffer + position, 1, sizeof(buffer) - position, stdout) ==
           sizeof(buffer) - position;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    const char *const *args = (const char *const *)argv;
    int64_t a;
    int64_t b;
    int64_t n;
    __int128 x;
    __int128 y;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s a b n\n", args[0]);
        return EXIT_FAILURE;
    }

    if (!parse_int64(args[1], &a) ||
        !parse_int64(args[2], &b) ||
        !parse_int64(args[3], &n)) {
        fputs("Invalid integer input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!solve_diophantine(a, b, n, &x, &y)) {
        if (puts("No solution") == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    if (fputs("x = ", stdout) == EOF ||
        !print_int128(x) ||
        fputs(", y = ", stdout) == EOF ||
        !print_int128(y) ||
        putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}