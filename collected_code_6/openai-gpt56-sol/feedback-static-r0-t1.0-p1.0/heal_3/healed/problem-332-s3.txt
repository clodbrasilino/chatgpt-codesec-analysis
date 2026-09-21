#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int count_character_frequency(
    const unsigned char *data,
    size_t length,
    size_t *frequencies,
    size_t frequency_count)
{
    const size_t required_count = (size_t)UCHAR_MAX + 1U;

    if ((data == NULL && length != 0U) ||
        frequencies == NULL ||
        frequency_count < required_count) {
        return -1;
    }

    for (size_t i = 0; i < frequency_count; ++i) {
        frequencies[i] = 0U;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t value = data[i];

        if (frequencies[value] == SIZE_MAX) {
            return -1;
        }

        ++frequencies[value];
    }

    return 0;
}

int main(void)
{
    const size_t input_capacity = 1024U;
    const size_t frequency_count = (size_t)UCHAR_MAX + 1U;
    unsigned char *input = malloc(input_capacity);
    size_t *frequencies = calloc(frequency_count, sizeof(*frequencies));
    size_t length = 0U;
    int character;
    int status = EXIT_FAILURE;

    if (input == NULL || frequencies == NULL) {
        goto cleanup;
    }

    while (length < input_capacity) {
        character = getchar();

        if (character == EOF) {
            break;
        }

        input[length++] = (unsigned char)character;

        if (character == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        goto cleanup;
    }

    if (count_character_frequency(
            input, length, frequencies, frequency_count) != 0) {
        goto cleanup;
    }

    for (size_t i = 0; i < frequency_count; ++i) {
        if (frequencies[i] != 0U &&
            printf("%u: %zu\n", (unsigned int)i, frequencies[i]) < 0) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(frequencies);
    free(input);
    return status;
}