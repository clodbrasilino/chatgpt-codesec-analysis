#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uintmax_t alphabets;
    uintmax_t digits;
    uintmax_t special_characters;
} CharacterCounts;

static int increment_counter(uintmax_t *counter)
{
    if (*counter == UINTMAX_MAX) {
        return 0;
    }

    ++(*counter);
    return 1;
}

static int count_characters(FILE *stream, CharacterCounts *counts)
{
    CharacterCounts result = {0, 0, 0};
    unsigned char buffer[4096];
    size_t bytes_read;

    if (stream == NULL || counts == NULL) {
        return 0;
    }

    while ((bytes_read = fread(buffer, 1, sizeof buffer, stream)) != 0) {
        for (size_t i = 0; i < bytes_read; ++i) {
            uintmax_t *counter;

            if (isalpha(buffer[i])) {
                counter = &result.alphabets;
            } else if (isdigit(buffer[i])) {
                counter = &result.digits;
            } else {
                counter = &result.special_characters;
            }

            if (!increment_counter(counter)) {
                return 0;
            }
        }
    }

    if (ferror(stream)) {
        return 0;
    }

    *counts = result;
    return 1;
}

int main(void)
{
    CharacterCounts counts;

    if (!count_characters(stdin, &counts)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    if (printf("Alphabets: %" PRIuMAX "\n"
               "Digits: %" PRIuMAX "\n"
               "Special characters: %" PRIuMAX "\n",
               counts.alphabets,
               counts.digits,
               counts.special_characters) < 0) {
        fputs("Failed to write output.\n", stderr);
        return 1;
    }

    return 0;
}