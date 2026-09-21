#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t highest_power_of_two(uint64_t number)
{
    if (number == UINT64_C(0)) {
        return UINT64_C(0);
    }

    uint64_t result = UINT64_C(1);

    while (result <= number / UINT64_C(2)) {
        result *= UINT64_C(2);
    }

    return result;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;

    if (getline(&line, &capacity, stdin) < 0) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(line, &end, 10);

    if (line == end || errno == ERANGE || parsed > UINT64_MAX) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    uint64_t number = (uint64_t)parsed;
    free(line);

    printf("%" PRIu64 "\n", highest_power_of_two(number));
    return EXIT_SUCCESS;
}