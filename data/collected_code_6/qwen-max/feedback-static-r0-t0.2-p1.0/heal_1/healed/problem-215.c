#include <stdio.h>
#include <stdlib.h>

void decode_rle(const int *encoded, int encoded_len, int **decoded, int *decoded_len) {
    *decoded = (int *)malloc(encoded_len * sizeof(int));
    if (*decoded == NULL) {
        exit(EXIT_FAILURE);
    }
    *decoded_len = 0;
    for (int i = 0; i < encoded_len; i += 2) {
        for (int j = 0; j < encoded[i]; ++j) {
            (*decoded)[(*decoded_len)++] = encoded[i + 1];
        }
    }
}

int main() {
    int encoded[] = {3, 2, 1, 5, 2, 7};
    int encoded_len = sizeof(encoded) / sizeof(encoded[0]);
    int *decoded = NULL;
    int decoded_len;

    decode_rle(encoded, encoded_len, &decoded, &decoded_len);

    for (int i = 0; i < decoded_len; ++i) {
        printf("%d ", decoded[i]);
    }
    printf("\n");

    free(decoded);
    return 0;
}