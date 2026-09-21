#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memchr'
  */

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t mod)
{
    return (a >= mod - b) ? a - (mod - b) : a + b;
}

static uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t mod)
{
    uint64_t result = 0;

    if (mod == 0) {
        return 0;
    }

    a %= mod;

    while (b != 0) {
        if ((b & UINT64_C(1)) != 0) {
            result = add_mod(result, a, mod);
        }

        b >>= 1;

        if (b != 0) {
            a = add_mod(a, a, mod);
        }
    }

    return result;
}

static uint64_t pow_mod(uint64_t base, uint64_t exponent, uint64_t mod)
{
    uint64_t result;

    if (mod == 0) {
        return 0;
    }

    result = UINT64_C(1) % mod;
    base %= mod;

    while (exponent != 0) {
        if ((exponent & UINT64_C(1)) != 0) {
            result = mul_mod(result, base, mod);
        }

        exponent >>= 1;

        if (exponent != 0) {
            base = mul_mod(base, base, mod);
        }
    }

    return result;
}

static int is_prime(uint64_t n)
{
    static const uint64_t witnesses[] = {
        UINT64_C(2), UINT64_C(325), UINT64_C(9375),
        UINT64_C(28178), UINT64_C(450775),
        UINT64_C(9780504), UINT64_C(1795265022)
    };
    static const uint64_t small_primes[] = {
        UINT64_C(2), UINT64_C(3), UINT64_C(5), UINT64_C(7),
        UINT64_C(11), UINT64_C(13), UINT64_C(17), UINT64_C(19),
        UINT64_C(23), UINT64_C(29), UINT64_C(31), UINT64_C(37)
    };
    uint64_t d;
    unsigned int s = 0;
    size_t i;

    if (n < UINT64_C(2)) {
        return 0;
    }

    for (i = 0; i < sizeof small_primes / sizeof small_primes[0]; ++i) {
        if (n == small_primes[i]) {
            return 1;
        }

        if (n % small_primes[i] == 0) {
            return 0;
        }
    }

    d = n - UINT64_C(1);

    while ((d & UINT64_C(1)) == 0) {
        d >>= 1;
        ++s;
    }

    for (i = 0; i < sizeof witnesses / sizeof witnesses[0]; ++i) {
        uint64_t a = witnesses[i] % n;
        uint64_t x;
        unsigned int r;

        if (a == 0) {
            continue;
        }

        x = pow_mod(a, d, n);

        if (x == UINT64_C(1) || x == n - UINT64_C(1)) {
            continue;
        }

        for (r = 1; r < s; ++r) {
            x = mul_mod(x, x, n);

            if (x == n - UINT64_C(1)) {
                break;
            }
        }

        if (r == s) {
            return 0;
        }
    }

    return 1;
}

static uint64_t ncr_digit_mod_prime(uint64_t n, uint64_t r, uint64_t p)
{
    uint64_t numerator = UINT64_C(1);
    uint64_t denominator = UINT64_C(1);
    uint64_t i;

    if (p < UINT64_C(2) || r > n) {
        return 0;
    }

    if (r > n - r) {
        r = n - r;
    }

    for (i = UINT64_C(1); i <= r; ++i) {
        numerator = mul_mod(numerator, n - r + i, p);
        denominator = mul_mod(denominator, i, p);
    }

    return mul_mod(
        numerator,
        pow_mod(denominator, p - UINT64_C(2), p),
        p
    );
}

static uint64_t ncr_mod_prime(uint64_t n, uint64_t r, uint64_t p)
{
    uint64_t result = UINT64_C(1);

    if (p < UINT64_C(2) || r > n) {
        return 0;
    }

    do {
        uint64_t ni = n % p;
        uint64_t ri = r % p;

        if (ri > ni) {
            return 0;
        }

        result = mul_mod(result, ncr_digit_mod_prime(ni, ri, p), p);
        n /= p;
        r /= p;
    } while (n != 0 || r != 0);

    return result;
}

static int is_space_character(int c)
{
    return c == ' ' || c == '\t' || c == '\n' ||
           c == '\r' || c == '\f' || c == '\v';
}

static int parse_uint64(const char **cursor, uint64_t *value)
{
    const char *start;
    char *end;
    uintmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    while (is_space_character((unsigned char)**cursor)) {
        ++*cursor;
    }

    start = *cursor;

    if (*start == '\0' || *start == '-' || *start == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *cursor = end;
    return 1;
}

static int discard_line_remainder(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[256];
    /* Possible weaknesses found:
     *  The scope of the variable 'count' can be reduced. [variableScope]
     */
    size_t count;

    do {
        count = fread(buffer, 1, sizeof buffer, stdin);

        if (count == 0) {
            return feof(stdin) && !ferror(stdin);
        }

        /* Possible weaknesses found:
         *  call to undeclared library function 'memchr' with type 'void *(const void *, int, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'memchr'
         *  implicit declaration of function 'memchr' [-Wimplicit-function-declaration]
         */
        if (memchr(buffer, '\n', count) != NULL) {
            return 1;
        }
    } while (!ferror(stdin));

    return 0;
}

static int read_line(char **line)
{
    enum { MAX_INPUT_LENGTH = 4096 };
    char *buffer;
    size_t length;
    int complete;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc((size_t)MAX_INPUT_LENGTH + 2U);

    if (buffer == NULL) {
        return 0;
    }

    if (fgets(buffer, MAX_INPUT_LENGTH + 2, stdin) == NULL) {
        free(buffer);
        return 0;
    }

    length = 0;
    while (length < (size_t)MAX_INPUT_LENGTH + 1U &&
           buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        complete = 1;
    } else if (length <= (size_t)MAX_INPUT_LENGTH && feof(stdin)) {
        complete = 1;
    } else {
        complete = 0;
    }

    if (!complete) {
        discard_line_remainder();
        free(buffer);
        return 0;
    }

    *line = buffer;
    return 1;
}

int main(void)
{
    char *input;
    const char *cursor;
    uint64_t n;
    uint64_t r;
    uint64_t p;
    uint64_t result;

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_uint64(&cursor, &n) ||
        !parse_uint64(&cursor, &r) ||
        !parse_uint64(&cursor, &p)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (is_space_character((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!is_prime(p)) {
        fputs("p must be prime\n", stderr);
        return EXIT_FAILURE;
    }

    result = ncr_mod_prime(n, r, p);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}