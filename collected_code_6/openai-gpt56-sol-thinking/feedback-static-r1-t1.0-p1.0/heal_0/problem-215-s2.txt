#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int decode_rle(const int *encoded, size_t encoded_length,
               int **decoded, size_t *decoded_length)
{
    size_t total = 0;
    size_t position = 0;
    int *result = NULL;

    if (decoded == NULL || decoded_length == NULL) {
        return -1;
    }

    *decoded = NULL;
    *decoded_length = 0;

    if ((encoded_length % 2U) != 0U ||
        (encoded == NULL && encoded_length != 0U)) {
        return -1;
    }

    for (size_t i = 0; i < encoded_length; i += 2U) {
        if (encoded[i] < 0) {
            return -1;
        }

        size_t count = (size_t)encoded[i];

        if (count > SIZE_MAX - total) {
            return -1;
        }

        total += count;
    }

    if (total == 0U) {
        return 0;
    }

    if (total > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = malloc(total * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < encoded_length; i += 2U) {
        size_t count = (size_t)encoded[i];
        int value = encoded[i + 1U];

        for (size_t j = 0; j < count; ++j) {
            result[position++] = value;
        }
    }

    *decoded = result;
    *decoded_length = total;
    return 0;
}

int main(void)
{
    const int encoded[] = {3, 1, 2, 4, 1, 7};
    const size_t encoded_length = sizeof(encoded) / sizeof(encoded[0]);
    int *decoded = NULL;
    size_t decoded_length = 0;

    if (decode_rle(encoded, encoded_length, &decoded, &decoded_length) != 0) {
        fputs("Failed to decode the list.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < decoded_length; ++i) {
        if (printf("%d%s", decoded[i],
                   i + 1U < decoded_length ? " " : "\n") < 0) {
            free(decoded);
            return EXIT_FAILURE;
        }
    }

    free(decoded);
    return EXIT_SUCCESS;
}