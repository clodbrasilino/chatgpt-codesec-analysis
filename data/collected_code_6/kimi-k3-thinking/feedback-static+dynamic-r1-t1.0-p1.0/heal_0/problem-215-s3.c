#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

int *rle_decode(const int *encoded, size_t encoded_len, size_t *decoded_len)
{
    size_t i;
    size_t j;
    size_t total;
    size_t alloc_count;
    size_t pos;
    int *decoded;

    if (encoded == NULL || decoded_len == NULL) {
        return NULL;
    }
    if (encoded_len % 2u != 0u) {
        return NULL;
    }

    total = 0u;
    for (i = 0u; i < encoded_len; i += 2u) {
        if (encoded[i] < 0) {
            return NULL;
        }
        if ((size_t)encoded[i] > SIZE_MAX - total) {
            return NULL;
        }
        total += (size_t)encoded[i];
    }

    if (total > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    alloc_count = (total == 0u) ? 1u : total;
    decoded = malloc(alloc_count * sizeof(int));
    if (decoded == NULL) {
        return NULL;
    }

    pos = 0u;
    for (i = 0u; i < encoded_len; i += 2u) {
        for (j = 0u; j < (size_t)encoded[i]; j++) {
            decoded[pos] = encoded[i + 1u];
            pos++;
        }
    }

    *decoded_len = total;
    return decoded;
}

int main(void)
{
    int encoded[] = {3, 1, 2, 4, 1, 5};
    size_t encoded_len;
    size_t decoded_len;
    size_t i;
    int *decoded;

    encoded_len = sizeof(encoded) / sizeof(encoded[0]);
    decoded_len = 0u;

    decoded = rle_decode(encoded, encoded_len, &decoded_len);
    if (decoded == NULL) {
        fprintf(stderr, "Failed to decode run-length encoded list\n");
        return EXIT_FAILURE;
    }

    printf("Decoded list: ");
    for (i = 0u; i < decoded_len; i++) {
        printf("%d ", decoded[i]);
    }
    printf("\n");

    free(decoded);
    decoded = NULL;

    return EXIT_SUCCESS;
}