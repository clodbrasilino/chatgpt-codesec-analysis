#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int sum_of_proper_divisors(unsigned long long number,
                                  unsigned long long *sum)
{
    unsigned long long divisor;
    unsigned long long result = 0;

    if (sum == NULL || number == 0) {
        return 0;
    }

    if (number == 1) {
        *sum = 0;
        return 1;
    }

    result = 1;

    for (divisor = 2; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0) {
            unsigned long long paired_divisor = number / divisor;

            if (result > ULLONG_MAX - divisor) {
                return 0;
            }
            result += divisor;

            if (paired_divisor != divisor) {
                if (result > ULLONG_MAX - paired_divisor) {
                    return 0;
                }
                result += paired_divisor;
            }
        }
    }

    *sum = result;
    return 1;
}

static int have_same_divisor_sum(unsigned long long first,
                                 unsigned long long second,
                                 int *same)
{
    unsigned long long first_sum;
    unsigned long long second_sum;

    if (same == NULL) {
        return 0;
    }

    if (!sum_of_proper_divisors(first, &first_sum) ||
        !sum_of_proper_divisors(second, &second_sum)) {
        return 0;
    }

    *same = first_sum == second_sum;
    return 1;
}

static int parse_positive_integer(const char *text, unsigned long long *value)
{
    char *end;
    unsigned long long parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || parsed == 0) {
        return 0;
    }

    *value = parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    unsigned long long first;
    unsigned long long second;
    int same;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <positive-integer> <positive-integer>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_positive_integer(argv[1], &first) ||
        !parse_positive_integer(argv[2], &second)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!have_same_divisor_sum(first, second, &same)) {
        fputs("Unable to calculate divisor sums.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(same ? "Same" : "Not same");
    return EXIT_SUCCESS;
}