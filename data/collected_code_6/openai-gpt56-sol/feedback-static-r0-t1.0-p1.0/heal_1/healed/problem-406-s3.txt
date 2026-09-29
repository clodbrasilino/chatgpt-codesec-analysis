#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int parity(unsigned long long value)
{
    unsigned int result = 0U;

    while (value != 0ULL) {
        result ^= 1U;
        value &= value - 1ULL;
    }

    return result;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    ssize_t length;
    char *end = NULL;
    unsigned long long value;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoull(input, &end, 0);

    if (errno != 0 || end == input) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%u\n", parity(value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}