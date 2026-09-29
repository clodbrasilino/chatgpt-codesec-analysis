#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef enum {
    RLE_SINGLE,
    RLE_RUN
} RLETag;

typedef struct {
    RLETag tag;
    int value;
    size_t count;
} RLEItem;

int rle_encode_modified(const int *data, size_t length, RLEItem *out, size_t out_capacity, size_t *out_count);
int rle_decode_modified(const RLEItem *items, size_t item_count, int *out, size_t out_capacity, size_t *out_length);

int rle_encode_modified(const int *data, size_t length, RLEItem *out, size_t out_capacity, size_t *out_count)
{
    size_t i = 0;
    size_t out_index = 0;

    if (out_count == NULL) {
        return -1;
    }
    *out_count = 0;

    if (length == 0) {
        return 0;
    }
    if (data == NULL || out == NULL) {
        return -1;
    }

    while (i < length) {
        size_t run = 1;
        while (i + run < length && data[i + run] == data[i]) {
            run++;
        }
        if (out_index >= out_capacity) {
            return -1;
        }
        out[out_index].value = data[i];
        out[out_index].count = run;
        out[out_index].tag = (run == 1) ? RLE_SINGLE : RLE_RUN;
        out_index++;
        i += run;
    }

    *out_count = out_index;
    return 0;
}

int rle_decode_modified(const RLEItem *items, size_t item_count, int *out, size_t out_capacity, size_t *out_length)
{
    size_t i;
    size_t out_index = 0;

    if (items == NULL || out == NULL || out_length == NULL) {
        return -1;
    }

    for (i = 0; i < item_count; i++) {
        size_t n = (items[i].tag == RLE_RUN) ? items[i].count : 1;
        size_t j;
        if (n > out_capacity - out_index) {
            return -1;
        }
        for (j = 0; j < n; j++) {
            out[out_index++] = items[i].value;
        }
    }

    *out_length = out_index;
    return 0;
}

int main(void)
{
    int data[] = {1, 1, 1, 2, 3, 3, 1, 1, 4, 5, 5, 5, 5};
    size_t length = sizeof(data) / sizeof(data[0]);
    RLEItem *encoded;
    int *decoded;
    size_t encoded_length = 0;
    size_t decoded_length = 0;
    size_t i;

    encoded = malloc(length * sizeof(*encoded));
    if (encoded == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (rle_encode_modified(data, length, encoded, length, &encoded_length) != 0) {
        fprintf(stderr, "Encoding failed\n");
        free(encoded);
        return EXIT_FAILURE;
    }

    printf("Encoded: ");
    for (i = 0; i < encoded_length; i++) {
        if (encoded[i].tag == RLE_RUN) {
            printf("(%zu, %d) ", encoded[i].count, encoded[i].value);
        } else {
            printf("%d ", encoded[i].value);
        }
    }
    printf("\n");

    decoded = malloc(length * sizeof(*decoded));
    if (decoded == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(encoded);
        return EXIT_FAILURE;
    }

    if (rle_decode_modified(encoded, encoded_length, decoded, length, &decoded_length) != 0) {
        fprintf(stderr, "Decoding failed\n");
        free(decoded);
        free(encoded);
        return EXIT_FAILURE;
    }

    printf("Decoded: ");
    for (i = 0; i < decoded_length; i++) {
        printf("%d ", decoded[i]);
    }
    printf("\n");

    free(decoded);
    free(encoded);
    return EXIT_SUCCESS;
}