#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <stdint.h>

#define INPUT_BUFFER_SIZE 64
#define DISCARD_GUARD_LIMIT 8192

static long sum_of_divisors(long n);
static bool read_long(const char *prompt, long *out);
static void discard_remaining_input(void);

static long sum_of_divisors(long n)
{
    long sum = 0;
    long i;

    if (n <= 0) {
        return 0;
    }

    for (i = 1; i <= n / i; i++) {
        if (n % i == 0) {
            long complement = n / i;

            if (sum > LONG_MAX - i) {
                return -1;
            }
            sum += i;

            if (i != complement) {
                if (sum > LONG_MAX - complement) {
                    return -1;
                }
                sum += complement;
            }
        }
    }

    return sum;
}

static void discard_remaining_input(void)
{
    int c;
    size_t guard = 0;

    do {
        c = getchar();
        guard++;
    } while (c != '\n' && c != EOF && guard < DISCARD_GUARD_LIMIT);
}

static bool read_long(const char *prompt, long *out)
{
    char buffer[INPUT_BUFFER_SIZE];
    char *endptr;
    long value;

    if (prompt == NULL || out == NULL) {
        return false;
    }

    printf("%s", prompt);
    fflush(stdout);

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        return false;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    if (memchr(buffer, '\n', sizeof(buffer)) == NULL && !feof(stdin)) {
        discard_remaining_input();
        return false;
    }

    errno = 0;
    value = strtol(buffer, &endptr, 10);

    if (endptr == buffer) {
        return false;
    }

    if (errno == ERANGE || value == LONG_MAX || value == LONG_MIN) {
        return false;
    }

    while (endptr < buffer + sizeof(buffer) && *endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            return false;
        }
        endptr++;
    }

    *out = value;
    return true;
}

int main(void)
{
    long num1;
    long num2;
    long sum1;
    long sum2;

    if (!read_long("Enter first number: ", &num1)) {
        fprintf(stderr, "Invalid input for first number.\n");
        return EXIT_FAILURE;
    }

    if (!read_long("Enter second number: ", &num2)) {
        fprintf(stderr, "Invalid input for second number.\n");
        return EXIT_FAILURE;
    }

    if (num1 <= 0 || num2 <= 0) {
        fprintf(stderr, "Numbers must be positive.\n");
        return EXIT_FAILURE;
    }

    sum1 = sum_of_divisors(num1);
    sum2 = sum_of_divisors(num2);

    if (sum1 < 0 || sum2 < 0) {
        fprintf(stderr, "Divisor sum overflow detected.\n");
        return EXIT_FAILURE;
    }

    if (sum1 == sum2) {
        printf("The sum of divisors of %ld and %ld are the same.\n", num1, num2);
    } else {
        printf("The sum of divisors of %ld and %ld are not the same.\n", num1, num2);
    }

    return EXIT_SUCCESS;
}