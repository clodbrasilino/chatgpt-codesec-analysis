#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

static int is_even(long number)
{
    return number % 2L == 0L;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&input, &capacity, stdin);

    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    long number = strtol(input, &end, 10);

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

    puts(is_even(number) ? "Even" : "Odd");

    free(input);
    return EXIT_SUCCESS;
}