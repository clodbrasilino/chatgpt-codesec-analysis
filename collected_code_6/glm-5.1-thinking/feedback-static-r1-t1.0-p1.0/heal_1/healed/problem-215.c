#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int* decode_rle(const int* encoded, size_t encoded_len, size_t* decoded_len) {
    if (encoded == NULL || decoded_len == NULL) {
        return NULL;
    }

    if (encoded_len == 0) {
        *decoded_len = 0;
        return NULL;
    }

    if (encoded_len % 2 != 0) {
        return NULL;
    }

    size_t total_len = 0;
    for (size_t i = 0; i < encoded_len; i += 2) {
        if (encoded[i] < 0) {
            return NULL;
        }
        size_t count = (size_t)encoded[i];
        if (total_len > SIZE_MAX - count) {
            return NULL;
        }
        total_len += count;
    }

    if (total_len == 0) {
        *decoded_len = 0;
        return NULL;
    }

    if (total_len > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int* decoded = (int*)malloc(total_len * sizeof(int));
    if (decoded == NULL) {
        return NULL;
    }

    size_t write_idx = 0;
    for (size_t i = 0; i < encoded_len; i += 2) {
        int count = encoded[i];
        int value = encoded[i + 1];
        for (int j = 0; j < count; j++) {
            decoded[write_idx++] = value;
        }
    }

    *decoded_len = total_len;
    return decoded;
}

int main(void) {
    int encoded[] = {3, 1, 2, 5, 1, 9, 0, 4};
    size_t encoded_len = ARRAY_SIZE(encoded);
    size_t decoded_len = SIZE_MAX;

    int* decoded = decode_rle(encoded, encoded_len, &decoded_len);

    if (decoded != NULL) {
        for (size_t i = 0; i < decoded_len; i++) {
            printf("%d ", decoded[i]);
        }
        printf("\n");
        free(decoded);
    } else if (decoded_len == 0) {
        printf("Input was empty.\n");
    } else {
        printf("Decoding failed.\n");
    }

    return 0;
}