#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *values;
    size_t *counts;
    size_t length;
} RLE;

static void rle_init(RLE *rle)
{
    rle->values = NULL;
    rle->counts = NULL;
    rle->length = 0;
}

static void rle_destroy(RLE *rle)
{
    if (rle == NULL) {
        return;
    }
    free(rle->values);
    free(rle->counts);
    rle->values = NULL;
    rle->counts = NULL;
    rle->length = 0;
}

static int rle_encode(const int *data, size_t size, RLE *rle)
{
    size_t i;
    size_t n;

    if (rle == NULL) {
        return -1;
    }
    rle_init(rle);

    if (size == 0) {
        return 0;
    }
    if (data == NULL) {
        return -1;
    }

    rle->values = malloc(size * sizeof *rle->values);
    if (rle->values == NULL) {
        return -1;
    }
    rle->counts = malloc(size * sizeof *rle->counts);
    if (rle->counts == NULL) {
        free(rle->values);
        rle->values = NULL;
        return -1;
    }

    n = 0;
    for (i = 0; i < size; i++) {
        if (n > 0 && rle->values[n - 1] == data[i]) {
            rle->counts[n - 1]++;
        } else {
            rle->values[n] = data[i];
            rle->counts[n] = 1;
            n++;
        }
    }
    rle->length = n;
    return 0;
}

static int rle_decode(const RLE *rle, int **out, size_t *out_size)
{
    size_t i;
    size_t j;
    size_t total;
    size_t pos;
    int *buffer;

    if (out == NULL || out_size == NULL) {
        return -1;
    }
    *out = NULL;
    *out_size = 0;

    if (rle == NULL) {
        return -1;
    }
    if (rle->length == 0) {
        return 0;
    }
    if (rle->values == NULL || rle->counts == NULL) {
        return -1;
    }

    total = 0;
    for (i = 0; i < rle->length; i++) {
        if (rle->counts[i] > SIZE_MAX - total) {
            return -1;
        }
        total += rle->counts[i];
    }
    if (total > SIZE_MAX / sizeof **out) {
        return -1;
    }

    buffer = malloc(total * sizeof *buffer);
    if (buffer == NULL) {
        return -1;
    }

    pos = 0;
    for (i = 0; i < rle->length; i++) {
        for (j = 0; j < rle->counts[i]; j++) {
            buffer[pos] = rle->values[i];
            pos++;
        }
    }

    *out = buffer;
    *out_size = total;
    return 0;
}

int main(void)
{
    int data[] = {4, 4, 4, 4, 9, 9, 1, 1, 1, 7, 7, 7, 7, 7};
    size_t data_size = sizeof data / sizeof data[0];
    RLE encoded;
    int *decoded;
    size_t decoded_size;
    size_t i;

    if (rle_encode(data, data_size, &encoded) != 0) {
        fprintf(stderr, "rle_encode failed\n");
        return EXIT_FAILURE;
    }

    printf("Input:  ");
    for (i = 0; i < data_size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    printf("Encoded:");
    for (i = 0; i < encoded.length; i++) {
        printf(" (%d x %zu)", encoded.values[i], encoded.counts[i]);
    }
    printf("\n");

    if (rle_decode(&encoded, &decoded, &decoded_size) != 0) {
        fprintf(stderr, "rle_decode failed\n");
        rle_destroy(&encoded);
        return EXIT_FAILURE;
    }

    printf("Decoded:");
    for (i = 0; i < decoded_size; i++) {
        printf(" %d", decoded[i]);
    }
    printf("\n");

    if (decoded_size != data_size) {
        free(decoded);
        rle_destroy(&encoded);
        return EXIT_FAILURE;
    }
    for (i = 0; i < data_size; i++) {
        if (decoded[i] != data[i]) {
            free(decoded);
            rle_destroy(&encoded);
            return EXIT_FAILURE;
        }
    }
    printf("Round-trip verified\n");

    free(decoded);
    rle_destroy(&encoded);
    return EXIT_SUCCESS;
}