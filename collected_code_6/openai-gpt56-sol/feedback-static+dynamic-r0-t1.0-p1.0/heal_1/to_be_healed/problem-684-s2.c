#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int count_occurrences(const char *text, char target, uint64_t length,
                             uint64_t *result)
{
    size_t text_length;
    uint64_t count_per_copy = 0;
    uint64_t count_remainder = 0;
    uint64_t copies;
    uint64_t remainder;

    if (text == NULL || result == NULL || text[0] == '\0') {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    text_length = strlen(text);

    for (size_t i = 0; i < text_length; ++i) {
        if (text[i] == target) {
            ++count_per_copy;
        }
    }

    copies = length / (uint64_t)text_length;
    remainder = length % (uint64_t)text_length;

    for (uint64_t i = 0; i < remainder; ++i) {
        if (text[i] == target) {
            ++count_remainder;
        }
    }

    if (count_per_copy != 0 &&
        copies > (UINT64_MAX - count_remainder) / count_per_copy) {
        return -1;
    }

    *result = copies * count_per_copy + count_remainder;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed_length;
    uint64_t result;

    if (argc != 4 || argv[2][0] == '\0' || argv[2][1] != '\0') {
        fprintf(stderr, "Usage: %s <string> <character> <length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    parsed_length = strtoumax(argv[3], &end, 10);
    if (argv[3][0] == '\0' || end == argv[3] || *end != '\0' ||
        parsed_length > UINT64_MAX) {
        fprintf(stderr, "Invalid length\n");
        return EXIT_FAILURE;
    }

    if (count_occurrences(argv[1], argv[2][0], (uint64_t)parsed_length,
                          &result) != 0) {
        fprintf(stderr, "Unable to count occurrences\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}