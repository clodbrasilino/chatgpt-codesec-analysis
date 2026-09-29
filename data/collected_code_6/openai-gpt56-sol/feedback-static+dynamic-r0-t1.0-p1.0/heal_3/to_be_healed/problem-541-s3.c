#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_abundant(unsigned long long number)
{
    unsigned long long sum = 1;

    if (number < 12) {
        return false;
    }

    for (unsigned long long divisor = 2;
         divisor <= number / divisor;
         ++divisor) {
        if (number % divisor == 0) {
            unsigned long long quotient = number / divisor;

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

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] != '\0') {
        return EXIT_FAILURE;
    } else {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = getchar();

        if (character != '\n' && character != EOF) {
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    char *end = NULL;
    unsigned long long number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || number == 0) {
        return EXIT_FAILURE;
    }

    puts(is_abundant(number) ? "Abundant" : "Not abundant");
    return EXIT_SUCCESS;
}