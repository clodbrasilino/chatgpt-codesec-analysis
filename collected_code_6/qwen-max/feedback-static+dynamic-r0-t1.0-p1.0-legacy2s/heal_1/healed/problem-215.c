#include <stdio.h>
#include <stdlib.h>

void decode_rle(const int *encoded, int encoded_size, int **decoded, int *decoded_size) {
    *decoded = (int *)malloc(encoded_size * sizeof(int));
    if (*decoded == NULL) return;
    *decoded_size = 0;
    
    for (int i = 0; i < encoded_size; i += 2) {
        for (int j = 0; j < encoded[i]; ++j) {
            (*decoded)[(*decoded_size)++] = encoded[i + 1];
        }
    }
}

int main() {
    const int encoded[] = {3, 2, 2, 5, 1, 7};
    int encoded_size = 6;
    int *decoded = NULL;
    int decoded_size;

    decode_rle(encoded, encoded_size, &decoded, &decoded_size);
    
    for (int i = 0; i < decoded_size; ++i) {
        printf("%d ", decoded[i]);
    }

    free(decoded);
    return 0;
}