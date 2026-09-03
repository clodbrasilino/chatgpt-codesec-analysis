#include <stdio.h>
#include <stdlib.h>

int *decode_rle(int *encoded, int size, int *decoded_size) {
    if (encoded == NULL || size <= 0 || decoded_size == NULL) {
        return NULL;
    }

    int total_size = 0;
    for (int i = 0; i < size; i += 2) {
        if (i + 1 >= size) {
            return NULL;
        }
        if (encoded[i] < 0) {
            return NULL;
        }
        total_size += encoded[i];
    }

    int *decoded = (int *)malloc(total_size * sizeof(int));
    if (decoded == NULL) {
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < size; i += 2) {
        int count = encoded[i];
        int value = encoded[i + 1];
        for (int j = 0; j < count; j++) {
            decoded[index++] = value;
        }
    }

    *decoded_size = total_size;
    return decoded;
}

int main(void) {
    int encoded[] = {3, 5, 2, 8, 1, 9};
    int encoded_size = sizeof(encoded) / sizeof(encoded[0]);
    int decoded_size = 0;

    int *decoded = decode_rle(encoded, encoded_size, &decoded_size);
    if (decoded == NULL) {
        printf("Decoding failed\n");
        return 1;
    }

    for (int i = 0; i < decoded_size; i++) {
        printf("%d ", decoded[i]);
    }
    printf("\n");

    free(decoded);
    return 0;
}