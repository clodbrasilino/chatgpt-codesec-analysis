#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} RLEPair;

RLEPair *rle_encode(const int *data, size_t length, size_t *out_length)
{
    if (data == NULL || out_length == NULL) {
        return NULL;
    }

    if (length == 0) {
        *out_length = 0;
        return NULL;
    }

    RLEPair *encoded = malloc(length * sizeof(*encoded));
    if (encoded == NULL) {
        return NULL;
    }

    size_t out = 0;
    encoded[out].value = data[0];
    encoded[out].count = 1;

    for (size_t i = 1; i < length; i++) {
        if (data[i] == encoded[out].value) {
            encoded[out].count++;
        } else {
            out++;
            encoded[out].value = data[i];
            encoded[out].count = 1;
        }
    }
    out++;

    RLEPair *resized = realloc(encoded, out * sizeof(*resized));
    if (resized != NULL) {
        encoded = resized;
    }

    *out_length = out;
    return encoded;
}

int main(void)
{
    int data[] = {1, 1, 1, 2, 2, 3, 4, 4, 4, 4, 5};
    size_t length = sizeof(data) / sizeof(data[0]);
    size_t encoded_length = 0;

    RLEPair *encoded = rle_encode(data, length, &encoded_length);
    if (encoded == NULL) {
        fprintf(stderr, "Run-length encoding failed\n");
        return EXIT_FAILURE;
    }

    printf("Run-length encoding: ");
    for (size_t i = 0; i < encoded_length; i++) {
        printf("(%d, %zu) ", encoded[i].value, encoded[i].count);
    }
    printf("\n");

    free(encoded);
    return EXIT_SUCCESS;
}