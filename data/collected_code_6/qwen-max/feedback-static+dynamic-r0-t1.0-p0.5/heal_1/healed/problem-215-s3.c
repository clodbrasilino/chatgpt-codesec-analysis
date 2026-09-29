#include <stdio.h>
#include <stdlib.h>

void decode_rle(const int *encoded, int encoded_len, int **decoded, int *decoded_len) {
    *decoded = (int *)malloc(encoded_len * sizeof(int));
    if (*decoded == NULL) {
        return;
    }
    int index = 0;
    for (int i = 0; i < encoded_len; i += 2) {
        for (int j = 0; j < encoded[i]; ++j) {
            (*decoded)[index++] = encoded[i + 1];
        }
    }
    *decoded_len = index;
}

int main() {
    const int encoded[] = {3, 2, 1, 5, 2, 8};
    int encoded_len = sizeof(encoded) / sizeof(encoded[0]);
    int *decoded = NULL;
    int decoded_len = 0;

    decode_rle(encoded, encoded_len, &decoded, &decoded_len);

    for (int i = 0; i < decoded_len; ++i) {
        printf("%d ", decoded[i]);
    }

    free(decoded);
    return 0;
}