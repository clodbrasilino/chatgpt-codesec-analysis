#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <limits.h>

static int count_occurrences(const char *string, size_t string_length,
                             uint64_t length, char target, uint64_t *result)
{
    uint64_t full_repetitions;
    size_t remainder;
    uint64_t occurrences_per_string = 0;
    uint64_t occurrences_in_remainder = 0;

    if (string == NULL || result == NULL || string_length == 0 ||
        string_length > UINT64_MAX) {
        return -1;
    }

    for (size_t i = 0; i < string_length; ++i) {
        if (string[i] == target) {
            ++occurrences_per_string;
        }
    }

    full_repetitions = length / (uint64_t)string_length;
    remainder = (size_t)(length % (uint64_t)string_length);

    for (size_t i = 0; i < remainder; ++i) {
        if (string[i] == target) {
            ++occurrences_in_remainder;
        }
    }

    if (occurrences_per_string != 0 &&
        full_repetitions >
            (UINT64_MAX - occurrences_in_remainder) /
                occurrences_per_string) {
        return -1;
    }

    *result = full_repetitions * occurrences_per_string +
              occurrences_in_remainder;

    return 0;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-' || text[0] == '+') {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > UINT64_MAX) {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

int main(int argc, char *argv[])
{
    size_t string_length;
    uint64_t repeated_length;
    uint64_t count;

    if (argc != 4 || argv[1] == NULL || argv[2] == NULL ||
        argv[3] == NULL || argv[2][0] == '\0' ||
        argv[2][1] != '\0') {
        fprintf(stderr, "Usage: %s <string> <character> <length>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    string_length = strnlen(argv[1], SIZE_MAX);
    if (string_length == 0 || string_length == SIZE_MAX) {
        fprintf(stderr, "Invalid string\n");
        return EXIT_FAILURE;
    }

    if (parse_uint64(argv[3], &repeated_length) != 0) {
        fprintf(stderr, "Invalid length\n");
        return EXIT_FAILURE;
    }

    if (count_occurrences(argv[1], string_length, repeated_length,
                          argv[2][0], &count) != 0) {
        fprintf(stderr, "Unable to count occurrences\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", count);
    return EXIT_SUCCESS;
}