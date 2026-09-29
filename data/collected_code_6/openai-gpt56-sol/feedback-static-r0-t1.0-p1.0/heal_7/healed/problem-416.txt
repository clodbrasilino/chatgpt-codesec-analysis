#define _POSIX_C_SOURCE 200809L

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

static int read_value(uint64_t *result)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return 0;
    }

    while (length > 0 &&
           (line[length - 1] == '\n' || line[length - 1] == '\r')) {
        line[--length] = '\0';
    }

    if (!feof(stdin)) {
        char *extra = NULL;
        size_t extra_capacity = 0;
        ssize_t extra_length = getline(&extra, &extra_capacity, stdin);

        if (extra_length >= 0) {
            free(extra);
            free(line);
            return 0;
        }

        free(extra);

        if (ferror(stdin)) {
            free(line);
            return 0;
        }
    }

    char *start = line;

    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        free(line);
        return 0;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || value > UINT64_MAX) {
        free(line);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *result = (uint64_t)value;
    free(line);
    return 1;
}

int main(void)
{
    uint64_t value;

    if (!read_value(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", max_exchange_sum(value));
    return EXIT_SUCCESS;
}