#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int parity(unsigned long long number)
{
    unsigned int result = 0U;

    while (number != 0ULL) {
        result ^= 1U;
        number &= number - 1ULL;
    }

    return result;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    ssize_t length;
    char *end = NULL;
    unsigned long long number;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(input, &end, 0);

    if (end == input || errno == ERANGE) {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid trailing characters.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%u\n", parity(number));
    free(input);
    return EXIT_SUCCESS;
}