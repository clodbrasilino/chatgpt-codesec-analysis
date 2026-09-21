#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t mod)
{
    a %= mod;
    b %= mod;
    return a >= mod - b ? a - (mod - b) : a + b;
}

static uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t mod)
{
    uint64_t result = 0;

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
    uint64_t result = UINT64_C(1) % mod;

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

    if (r > n) {
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

    if (r > n) {
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
    } while (n != 0);

    return result;
}

static int read_input_line(char **line)
{
    enum { MAX_INPUT_LENGTH = 4096 };
    size_t length = 0;
    size_t capacity = 128;
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
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return -1;
            }

            if (length == 0) {
                free(buffer);
                return 0;
            }

            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length >= MAX_INPUT_LENGTH) {
            while (ch != '\n' && ch != EOF) {
                ch = fgetc(stdin);
            }

            free(buffer);
            return ch == EOF && ferror(stdin) ? -1 : -2;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            new_capacity = capacity * 2;

            if (new_capacity > (size_t)MAX_INPUT_LENGTH + 1) {
                new_capacity = (size_t)MAX_INPUT_LENGTH + 1;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return -1;
            }

            resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (length != 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int parse_value(const char **cursor, uint64_t *value)
{
    const unsigned char *p;
    uint64_t parsed = 0;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    p = (const unsigned char *)*cursor;

    while (*p != '\0' && isspace(*p)) {
        ++p;
    }

    if (*p == '\0' || !isdigit(*p)) {
        return 0;
    }

    do {
        unsigned int digit = (unsigned int)(*p - (unsigned char)'0');

        if (parsed > (UINT64_MAX - digit) / UINT64_C(10)) {
            return 0;
        }

        parsed = parsed * UINT64_C(10) + digit;
        ++p;
    } while (*p != '\0' && isdigit(*p));

    if (*p != '\0' && !isspace(*p)) {
        return 0;
    }

    *value = parsed;
    *cursor = (const char *)p;
    return 1;
}

static int parse_input(const char *input, uint64_t *n, uint64_t *r, uint64_t *p)
{
    const char *cursor;

    if (input == NULL || n == NULL || r == NULL || p == NULL) {
        return 0;
    }

    cursor = input;

    if (!parse_value(&cursor, n) ||
        !parse_value(&cursor, r) ||
        !parse_value(&cursor, p)) {
        return 0;
    }

    while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    return *cursor == '\0';
}

int main(void)
{
    char *input = NULL;
    uint64_t n;
    uint64_t r;
    uint64_t p;
    uint64_t result;
    int read_status = read_input_line(&input);

    if (read_status <= 0) {
        if (read_status == -1) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Invalid input\n", stderr);
        }

        free(input);
        return EXIT_FAILURE;
    }

    if (!parse_input(input, &n, &r, &p)) {
        fputs("Invalid input\n", stderr);
        free(input);
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