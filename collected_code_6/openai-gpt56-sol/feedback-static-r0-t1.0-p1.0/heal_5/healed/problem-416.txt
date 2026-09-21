#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t max_exchange_sum(uint64_t number)
{
    if (number < UINT64_C(12)) {
        return number;
    }

    uint64_t half = max_exchange_sum(number / UINT64_C(2));
    uint64_t third = max_exchange_sum(number / UINT64_C(3));
    uint64_t quarter = max_exchange_sum(number / UINT64_C(4));

    if (half > UINT64_MAX - third) {
        return UINT64_MAX;
    }

    uint64_t sum = half + third;

    if (sum > UINT64_MAX - quarter) {
        return UINT64_MAX;
    }

    sum += quarter;
    return sum > number ? sum : number;
}

int main(void)
{
    char input[128];

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    size_t length = 0;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof input) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        int character = fgetc(stdin);

        if (character != EOF) {
            while (character != '\n' && character != EOF) {
                character = fgetc(stdin);
            }

            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    char *start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", max_exchange_sum((uint64_t)value));
    return EXIT_SUCCESS;
}