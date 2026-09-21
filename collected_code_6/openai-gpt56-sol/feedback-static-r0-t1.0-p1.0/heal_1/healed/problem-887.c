#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

static int is_odd(long long number)
{
    return (number & 1LL) != 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    long long number;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoll(input, &end, 10);

    if (end == input || errno == ERANGE) {
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

    if (printf("%s\n", is_odd(number) ? "Odd" : "Not odd") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}