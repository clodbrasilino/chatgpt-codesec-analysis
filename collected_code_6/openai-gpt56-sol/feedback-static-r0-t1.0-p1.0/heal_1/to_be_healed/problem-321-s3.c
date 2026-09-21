#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int is_demlo_number(unsigned long long number)
{
    unsigned long long root = 0;
    unsigned long long square = 0;
    unsigned long long increment = 1;

    while (square < number) {
        if (square > ULLONG_MAX - increment) {
            return 0;
        }

        square += increment;

        if (root == ULLONG_MAX || increment > ULLONG_MAX - 2U) {
            return 0;
        }

        ++root;
        increment += 2U;
    }

    if (square != number) {
        return 0;
    }

    do {
        if (number % 10U != 1U) {
            return 0;
        }
        number /= 10U;

        if (number == 0U) {
            return 1;
        }

        while (number % 10U == 2U) {
            number /= 10U;
        }

        if (number == 0U) {
            return 0;
        }
    } while (number % 10U == 1U);

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

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    printf("%s\n", is_demlo_number(number) ? "Demlo number" : "Not a Demlo number");
    return EXIT_SUCCESS;
}