#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int sum_of_divisors(uint64_t number, uint64_t *sum)
{
    uint64_t divisor;
    uint64_t result = 0;

    if (number == 0 || sum == NULL) {
        return 0;
    }

    for (divisor = 1; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0) {
            uint64_t paired_divisor = number / divisor;

            if (UINT64_MAX - result < divisor) {
                return 0;
            }
            result += divisor;

            if (paired_divisor != divisor) {
                if (UINT64_MAX - result < paired_divisor) {
                    return 0;
                }
                result += paired_divisor;
            }
        }
    }

    *sum = result;
    return 1;
}

int main(void)
{
    uint64_t number;
    uint64_t sum;
    char extra;

    if (printf("Enter a positive integer: ") < 0) {
        return 1;
    }

    if (scanf("%" SCNu64, &number) != 1 || number == 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    if (scanf(" %c", &extra) == 1) {
        fprintf(stderr, "Unexpected input.\n");
        return 1;
    }

    if (!sum_of_divisors(number, &sum)) {
        fprintf(stderr, "Unable to calculate the sum.\n");
        return 1;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return 1;
    }

    return 0;
}