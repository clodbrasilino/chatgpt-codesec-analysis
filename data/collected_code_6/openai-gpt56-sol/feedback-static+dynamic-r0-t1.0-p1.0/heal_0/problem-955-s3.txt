#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_abundant(unsigned long long number)
{
    if (number < 12) {
        return false;
    }

    unsigned long long divisor_sum = 1;

    for (unsigned long long divisor = 2; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0) {
            unsigned long long paired_divisor = number / divisor;

            if (divisor_sum > number - divisor) {
                return true;
            }
            divisor_sum += divisor;

            if (paired_divisor != divisor) {
                if (divisor_sum > number - paired_divisor) {
                    return true;
                }
                divisor_sum += paired_divisor;
            }
        }
    }

    return divisor_sum > number;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long number = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || number == 0) {
        fprintf(stderr, "Invalid positive integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("%llu is %sabundant.\n", number, is_abundant(number) ? "" : "not ");

    return EXIT_SUCCESS;
}