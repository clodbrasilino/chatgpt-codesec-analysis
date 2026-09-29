#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} RLEPair;

int* decode_rle(const RLEPair* encoded, size_t encoded_len, size_t* decoded_len) {
    if (encoded == NULL || decoded_len == NULL) {
        return NULL;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < encoded_len; ++i) {
        if (encoded[i].count < 0) {
            return NULL;
        }
        total_length += (size_t)encoded[i].count;
    }

    int* decoded = (int*)malloc(total_length * sizeof(int));
    if (decoded == NULL) {
        return NULL;
    }

    size_t current_index = 0;
    for (size_t i = 0; i < encoded_len; ++i) {
        for (int j = 0; j < encoded[i].count; ++j) {
            decoded[current_index++] = encoded[i].value;
        }
    }

    *decoded_len = total_length;
    return decoded;
}

int main(void) {
    RLEPair encoded[] = {
        {1, 3},
        {2, 1},
        {3, 4},
        {4, 2}
    };
    size_t encoded_len = sizeof(encoded) / sizeof(encoded[0]);
    size_t decoded_len = 0;

    int* decoded = decode_rle(encoded, encoded_len, &decoded_len);

    if (decoded != NULL) {
        for (size_t i = 0; i < decoded_len; ++i) {
            printf("%d ", decoded[i]);
        }
        printf("\n");
        free(decoded);
    } else {
        printf("Error decoding RLE.\n");
    }

    return 0;
}