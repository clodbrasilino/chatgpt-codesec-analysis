#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int has_odd_divisor_count(unsigned long long number)
{
    unsigned long long low = 0;
    unsigned long long high = number < UINT_MAX ? number : UINT_MAX;

    while (low <= high) {
        unsigned long long mid = low + (high - low) / 2;

        if (mid != 0 && mid == number / mid && number % mid == 0) {
            return 1;
        }

        /* Possible weaknesses found:
         *  Assuming that condition 'mid==0' is not redundant
         */
        if (mid == 0 || mid < number / mid) {
            low = mid + 1;
        } else {
            /* Possible weaknesses found:
             *  Condition 'mid==0' is always false [knownConditionTrueFalse]
             *  Condition 'mid==0' is always false
             */
            if (mid == 0) {
                break;
            }
            high = mid - 1;
        }
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end = NULL;
    unsigned long long number;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input || number == 0) {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(has_odd_divisor_count(number) ? "Odd" : "Even");
    return EXIT_SUCCESS;
}