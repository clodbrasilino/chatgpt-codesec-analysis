#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int *rle_decode(const int *encoded, size_t encoded_len, size_t *decoded_len)
{
    size_t i;
    size_t total = 0;
    size_t pos = 0;
    int *decoded = NULL;

    if (encoded == NULL || decoded_len == NULL) {
        return NULL;
    }
    if (encoded_len % 2 != 0) {
        return NULL;
    }

    for (i = 0; i < encoded_len; i += 2) {
        if (encoded[i + 1] < 0) {
            return NULL;
        }
        if ((size_t)encoded[i + 1] > SIZE_MAX - total) {
            return NULL;
        }
        total += (size_t)encoded[i + 1];
    }

    if (total == 0) {
        *decoded_len = 0;
        return NULL;
    }
    if (total > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    decoded = (int *)malloc(total * sizeof(int));
    if (decoded == NULL) {
        return NULL;
    }

    for (i = 0; i < encoded_len; i += 2) {
        int j;
        for (j = 0; j < encoded[i + 1]; j++) {
            decoded[pos++] = encoded[i];
        }
    }

    *decoded_len = total;
    return decoded;
}

int main(void)
{
    int encoded[] = {1, 3, 2, 2, 5, 4};
    size_t encoded_len = sizeof(encoded) / sizeof(encoded[0]);
    size_t decoded_len = 0;
    size_t i;
    int *decoded = rle_decode(encoded, encoded_len, &decoded_len);

    if (decoded == NULL) {
        fprintf(stderr, "Failed to decode run-length encoded list\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < decoded_len; i++) {
        printf("%d ", decoded[i]);
    }
    printf("\n");

    free(decoded);
    decoded = NULL;

    return EXIT_SUCCESS;
}