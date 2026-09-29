#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_undulating(unsigned long long number)
{
    unsigned int first = (unsigned int)(number % 10ULL);
    number /= 10ULL;

    if (number == 0ULL) {
        return false;
    }

    unsigned int second = (unsigned int)(number % 10ULL);
    number /= 10ULL;

    if (first == second) {
        return false;
    }

    bool expect_first = true;

    while (number != 0ULL) {
        unsigned int digit = (unsigned int)(number % 10ULL);

        if (digit != (expect_first ? first : second)) {
            return false;
        }

        expect_first = !expect_first;
        number /= 10ULL;
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    char *end = NULL;
    unsigned long long number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(input, &end, 10);

    if (errno != 0 || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    puts(is_undulating(number) ? "Undulating" : "Not undulating");
    return EXIT_SUCCESS;
}