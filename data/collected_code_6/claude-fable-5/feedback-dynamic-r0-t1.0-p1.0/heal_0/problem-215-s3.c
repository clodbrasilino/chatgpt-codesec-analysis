#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

typedef struct {
    size_t count;
    int value;
} RlePair;

static int *decode_rle(const RlePair *encoded, size_t pair_count, size_t *out_length)
{
    size_t total = 0;
    size_t i;
    size_t j;
    size_t pos = 0;
    int *result = NULL;

    if (encoded == NULL || out_length == NULL) {
        return NULL;
    }

    for (i = 0; i < pair_count; i++) {
        if (encoded[i].count > (SIZE_MAX - total)) {
            return NULL;
        }
        total += encoded[i].count;
    }

    if (total == 0) {
        *out_length = 0;
        return NULL;
    }

    if (total > (SIZE_MAX / sizeof(int))) {
        return NULL;
    }

    result = malloc(total * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < pair_count; i++) {
        for (j = 0; j < encoded[i].count; j++) {
            result[pos] = encoded[i].value;
            pos++;
        }
    }

    *out_length = total;
    return result;
}

int main(void)
{
    RlePair encoded[] = {
        {3, 7},
        {1, 2},
        {4, 9},
        {2, 5}
    };
    size_t pair_count = sizeof(encoded) / sizeof(encoded[0]);
    size_t decoded_length = 0;
    int *decoded = NULL;
    size_t i;

    decoded = decode_rle(encoded, pair_count, &decoded_length);
    if (decoded == NULL && decoded_length != 0) {
        fprintf(stderr, "Decoding failed\n");
        return EXIT_FAILURE;
    }

    if (decoded == NULL) {
        printf("Decoded list is empty\n");
        return EXIT_SUCCESS;
    }

    printf("Decoded list:");
    for (i = 0; i < decoded_length; i++) {
        printf(" %d", decoded[i]);
    }
    printf("\n");

    free(decoded);
    decoded = NULL;

    return EXIT_SUCCESS;
}