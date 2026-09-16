#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int sum_of_divisors(uint64_t number, uint64_t *result)
{
    uint64_t sum = 0;

    if (number == 0 || result == NULL) {
        return 0;
    }

    for (uint64_t divisor = 1; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0) {
            uint64_t paired_divisor = number / divisor;

            if (UINT64_MAX - sum < divisor) {
                return 0;
            }
            sum += divisor;

            if (paired_divisor != divisor) {
                if (UINT64_MAX - sum < paired_divisor) {
                    return 0;
                }
                sum += paired_divisor;
            }
        }
    }

    *result = sum;
    return 1;
}

int main(void)
{
    uint64_t number;
    uint64_t sum;

    if (scanf("%" SCNu64, &number) != 1 || number == 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (!sum_of_divisors(number, &sum)) {
        fprintf(stderr, "Unable to calculate the divisor sum\n");
        return 1;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return 1;
    }

    return 0;
}