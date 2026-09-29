#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_abundant(unsigned long long number)
{
    unsigned long long divisor;
    unsigned long long sum = 1U;

    if (number < 12U) {
        return false;
    }

    for (divisor = 2U; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0U) {
            const unsigned long long quotient = number / divisor;

            if (sum > number - divisor) {
                return true;
            }
            sum += divisor;

            if (quotient != divisor) {
                if (sum > number - quotient) {
                    return true;
                }
                sum += quotient;
            }
        }
    }

    return sum > number;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end = NULL;
    unsigned long long number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || number == 0U) {
        return EXIT_FAILURE;
    }

    puts(is_abundant(number) ? "Abundant" : "Not abundant");
    return EXIT_SUCCESS;
}