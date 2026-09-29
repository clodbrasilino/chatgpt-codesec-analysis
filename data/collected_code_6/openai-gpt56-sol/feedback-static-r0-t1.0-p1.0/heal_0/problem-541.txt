#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_abundant(unsigned long long number)
{
    unsigned long long sum = 1;

    if (number < 12) {
        return false;
    }

    for (unsigned long long divisor = 2; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0) {
            unsigned long long paired_divisor = number / divisor;

            if (sum > number - divisor) {
                return true;
            }
            sum += divisor;

            if (paired_divisor != divisor) {
                if (sum > number - paired_divisor) {
                    return true;
                }
                sum += paired_divisor;
            }
        }
    }

    return sum > number;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long number;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || number == 0 || number == ULLONG_MAX) {
        fprintf(stderr, "Invalid positive integer\n");
        return EXIT_FAILURE;
    }

    printf("%llu is %sabundant.\n", number, is_abundant(number) ? "" : "not ");

    return EXIT_SUCCESS;
}