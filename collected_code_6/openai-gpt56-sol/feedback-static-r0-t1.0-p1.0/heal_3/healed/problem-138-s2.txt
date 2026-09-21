#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_sum_of_nonzero_powers_of_two(unsigned long long number)
{
    return number >= 2ULL && (number & 1ULL) == 0ULL;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;

    if (getline(&input, &capacity, stdin) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    char *end = NULL;
    errno = 0;
    unsigned long long number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_sum_of_nonzero_powers_of_two(number) ? "Yes" : "No");

    free(input);
    return EXIT_SUCCESS;
}