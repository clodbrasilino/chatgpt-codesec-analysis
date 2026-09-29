#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int get_text_length(const char *text, size_t limit, size_t *length)
{
    size_t i;

    if (text == NULL || length == NULL) {
        return -1;
    }

    for (i = 0; i < limit; ++i) {
        if (text[i] == '\0') {
            *length = i;
            return i == 0 ? -1 : 0;
        }
    }

    return -1;
}

static int count_occurrences(const char *text, size_t text_capacity,
                             char target, uint64_t length, uint64_t *result)
{
    size_t text_length;
    uint64_t count_per_copy = 0;
    uint64_t count_remainder = 0;
    uint64_t copies;
    uint64_t remainder;
    size_t i;

    if (result == NULL ||
        get_text_length(text, text_capacity, &text_length) != 0) {
        return -1;
    }

    if (text_length > UINT64_MAX) {
        return -1;
    }

    for (i = 0; i < text_length; ++i) {
        if (text[i] == target) {
            ++count_per_copy;
        }
    }

    copies = length / (uint64_t)text_length;
    remainder = length % (uint64_t)text_length;

    for (i = 0; i < (size_t)remainder; ++i) {
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
    char *end;
    uintmax_t parsed_length;
    uint64_t result;
    size_t text_capacity;

    if (argc != 4 || argv[0] == NULL || argv[1] == NULL ||
        argv[2] == NULL || argv[3] == NULL ||
        argv[2][0] == '\0' || argv[2][1] != '\0') {
        fprintf(stderr, "Usage: %s <string> <character> <length>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed_length = strtoumax(argv[3], &end, 10);

    if (argv[3][0] == '\0' || argv[3][0] == '-' ||
        end == argv[3] || end == NULL || *end != '\0' ||
        errno == ERANGE || parsed_length > UINT64_MAX) {
        fprintf(stderr, "Invalid length\n");
        return EXIT_FAILURE;
    }

    if (argc > 1 && argv[1] >= argv[0] && argv[1] < argv[argc - 1]) {
        text_capacity = (size_t)(argv[2] - argv[1]);
    } else {
        text_capacity = SIZE_MAX;
    }

    if (count_occurrences(argv[1], text_capacity, argv[2][0],
                          (uint64_t)parsed_length, &result) != 0) {
        fprintf(stderr, "Unable to count occurrences\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}