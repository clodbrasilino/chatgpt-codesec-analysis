#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

static int has_odd_parity(unsigned long long value)
{
    int parity = 0;

    while (value != 0ULL) {
        parity ^= 1;
        value &= value - 1ULL;
    }

    return parity;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
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

    if (errno == ERANGE || end == input) {
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

    printf("%s\n", has_odd_parity(value) ? "Odd parity" : "Even parity");

    free(input);
    return EXIT_SUCCESS;
}