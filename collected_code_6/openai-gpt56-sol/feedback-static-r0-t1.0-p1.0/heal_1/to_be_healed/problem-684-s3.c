#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int count_occurrences(const char *string, char target, uint64_t length,
                             uint64_t *result)
{
    size_t string_length;
    uint64_t occurrences_per_repeat = 0;
    uint64_t remainder_occurrences = 0;
    uint64_t complete_repeats;
    size_t remainder;

    if (string == NULL || result == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    string_length = strlen(string);
    if (string_length == 0) {
        return -1;
    }

    for (size_t i = 0; i < string_length; ++i) {
        if (string[i] == target) {
            ++occurrences_per_repeat;
        }
    }

    complete_repeats = length / (uint64_t)string_length;
    remainder = (size_t)(length % (uint64_t)string_length);

    for (size_t i = 0; i < remainder; ++i) {
        if (string[i] == target) {
            ++remainder_occurrences;
        }
    }

    if (occurrences_per_repeat != 0 &&
        complete_repeats > (UINT64_MAX - remainder_occurrences) /
                               occurrences_per_repeat) {
        return -1;
    }

    *result = complete_repeats * occurrences_per_repeat +
              remainder_occurrences;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uint64_t length;
    uint64_t count;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (argc != 4 || argv[1][0] == '\0' || strlen(argv[2]) != 1) {
        fprintf(stderr, "Usage: %s <string> <character> <length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    length = strtoumax(argv[3], &end, 10);

    if (errno == ERANGE || end == argv[3] || *end != '\0' ||
        argv[3][0] == '-') {
        fprintf(stderr, "Invalid length\n");
        return EXIT_FAILURE;
    }

    if (count_occurrences(argv[1], argv[2][0], length, &count) != 0) {
        fprintf(stderr, "Unable to calculate the occurrence count\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}