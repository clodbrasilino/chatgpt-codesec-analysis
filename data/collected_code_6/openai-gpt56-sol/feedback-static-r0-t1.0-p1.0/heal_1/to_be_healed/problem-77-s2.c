#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int digit_sum_difference(const char *number)
{
    int even_sum = 0;
    int odd_sum = 0;

    if (*number == '+' || *number == '-') {
        ++number;
    }

    while (*number != '\0') {
        int digit = *number - '0';

        if (digit % 2 == 0) {
            even_sum += digit;
        } else {
            odd_sum += digit;
        }

        ++number;
    }

    return even_sum - odd_sum;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    char *end = NULL;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    (void)strtoll(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    printf("%d\n", digit_sum_difference(input));

    return EXIT_SUCCESS;
}