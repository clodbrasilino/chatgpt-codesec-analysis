#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_lucid(uint64_t value)
{
    if (value == 0) {
        return 0;
    }

    while (value != 0) {
        uint64_t digit = value % 10U;

        if (digit != 4U && digit != 7U) {
            return 0;
        }

        value /= 10U;
    }

    return 1;
}

static uint64_t largest_lucid_at_most(uint64_t n)
{
    while (n != 0) {
        if (is_lucid(n)) {
            return n;
        }

        --n;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || input > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = largest_lucid_at_most((uint64_t)input);

    if (result == 0) {
        fprintf(stderr, "No lucid number is less than or equal to %" PRIuMAX "\n", input);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}