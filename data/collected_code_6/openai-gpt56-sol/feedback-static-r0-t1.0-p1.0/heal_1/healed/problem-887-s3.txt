#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_odd(long number)
{
    return ((unsigned long)number & 1UL) != 0UL;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    long number;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtol(input, &end, 10);

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

    printf("%s\n", is_odd(number) ? "Odd" : "Not odd");

    free(input);
    return EXIT_SUCCESS;
}