#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int has_odd_divisor_count(unsigned long long number)
{
    unsigned long long low = 1;
    unsigned long long high = number;

    while (low <= high) {
        unsigned long long middle = low + (high - low) / 2;
        unsigned long long quotient = number / middle;

        if (middle == quotient && number % middle == 0) {
            return 1;
        }

        if (middle > quotient) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *start;
    char *end;
    unsigned long long number;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    while (length > 0 &&
           (input[length - 1] == '\n' || input[length - 1] == '\r')) {
        input[--length] = '\0';
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start || number == 0) {
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

    puts(has_odd_divisor_count(number) ? "Odd" : "Even");

    free(input);
    return EXIT_SUCCESS;
}