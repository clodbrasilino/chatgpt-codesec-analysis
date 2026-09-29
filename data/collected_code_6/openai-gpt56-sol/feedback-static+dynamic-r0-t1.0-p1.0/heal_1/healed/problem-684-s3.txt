#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int count_occurrences(const char *string, size_t string_length,
                             unsigned char target, uint64_t length,
                             uint64_t *result)
{
    uint64_t occurrences_per_repeat = 0;
    uint64_t remainder_occurrences = 0;
    uint64_t complete_repeats;
    size_t remainder;

    if (string == NULL || result == NULL || string_length == 0) {
        return -1;
    }

    for (size_t i = 0; i < string_length; ++i) {
        if ((unsigned char)string[i] == target) {
            ++occurrences_per_repeat;
        }
    }

    complete_repeats = length / (uint64_t)string_length;
    remainder = (size_t)(length % (uint64_t)string_length);

    for (size_t i = 0; i < remainder; ++i) {
        if ((unsigned char)string[i] == target) {
            ++remainder_occurrences;
        }
    }

    if (occurrences_per_repeat != 0 &&
        complete_repeats >
            (UINT64_MAX - remainder_occurrences) / occurrences_per_repeat) {
        return -1;
    }

    *result = complete_repeats * occurrences_per_repeat +
              remainder_occurrences;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end;
    uintmax_t parsed_length;
    uint64_t length;
    uint64_t count;
    size_t string_length;
    size_t character_length;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <string> <character> <length>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    string_length = strnlen(argv[1], SIZE_MAX);
    character_length = strnlen(argv[2], 2);

    if (string_length == 0 || character_length != 1) {
        fprintf(stderr, "Usage: %s <string> <character> <length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[3][0] == '\0' || argv[3][0] == '-') {
        fprintf(stderr, "Invalid length\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed_length = strtoumax(argv[3], &end, 10);

    if (errno == ERANGE || end == argv[3] || *end != '\0' ||
        parsed_length > UINT64_MAX) {
        fprintf(stderr, "Invalid length\n");
        return EXIT_FAILURE;
    }

    length = (uint64_t)parsed_length;

    if (count_occurrences(argv[1], string_length,
                          (unsigned char)argv[2][0], length, &count) != 0) {
        fprintf(stderr, "Unable to calculate the occurrence count\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}