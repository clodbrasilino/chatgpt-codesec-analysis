#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_undulating(unsigned long long number)
{
    unsigned int first;
    unsigned int second;
    size_t digit_count = 0U;
    unsigned long long value = number;

    if (number < 100ULL) {
        return false;
    }

    first = (unsigned int)(value % 10ULL);
    value /= 10ULL;
    second = (unsigned int)(value % 10ULL);

    if (first == second) {
        return false;
    }

    while (value != 0ULL) {
        unsigned int digit = (unsigned int)(value % 10ULL);
        unsigned int expected = (digit_count % 2U == 0U) ? first : second;

        if (digit != expected) {
            return false;
        }

        ++digit_count;
        value /= 10ULL;
    }

    return true;
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

    if (*end != '\0' || input[0] == '-') {
        return EXIT_FAILURE;
    }

    puts(is_undulating(number) ? "Undulating" : "Not undulating");

    return EXIT_SUCCESS;
}