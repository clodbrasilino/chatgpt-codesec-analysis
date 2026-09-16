#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    MOST_COMMON_OK = 0,
    MOST_COMMON_INVALID_ARGUMENT,
    MOST_COMMON_EMPTY_STRING,
    MOST_COMMON_COUNT_OVERFLOW
} MostCommonStatus;

MostCommonStatus count_most_common_character(
    const char *string,
    unsigned char *character,
    size_t *frequency)
{
    size_t counts[(size_t)UCHAR_MAX + 1U] = {0};
    const unsigned char *cursor;
    size_t highest_count = 0U;
    unsigned char most_common = 0U;

    if (string == NULL || character == NULL || frequency == NULL) {
        return MOST_COMMON_INVALID_ARGUMENT;
    }

    if (string[0] == '\0') {
        return MOST_COMMON_EMPTY_STRING;
    }

    cursor = (const unsigned char *)string;

    while (*cursor != '\0') {
        if (counts[*cursor] == SIZE_MAX) {
            return MOST_COMMON_COUNT_OVERFLOW;
        }

        ++counts[*cursor];
        ++cursor;
    }

    cursor = (const unsigned char *)string;

    while (*cursor != '\0') {
        if (counts[*cursor] > highest_count) {
            highest_count = counts[*cursor];
            most_common = *cursor;
        }

        ++cursor;
    }

    *character = most_common;
    *frequency = highest_count;

    return MOST_COMMON_OK;
}

int main(int argc, char *argv[])
{
    unsigned char character;
    size_t frequency;
    MostCommonStatus status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    status = count_most_common_character(argv[1], &character, &frequency);

    if (status == MOST_COMMON_EMPTY_STRING) {
        fprintf(stderr, "The string must not be empty.\n");
        return EXIT_FAILURE;
    }

    if (status != MOST_COMMON_OK) {
        fprintf(stderr, "Unable to count characters.\n");
        return EXIT_FAILURE;
    }

    if (printf("Most common character: '%c'\nFrequency: %zu\n",
               character, frequency) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}