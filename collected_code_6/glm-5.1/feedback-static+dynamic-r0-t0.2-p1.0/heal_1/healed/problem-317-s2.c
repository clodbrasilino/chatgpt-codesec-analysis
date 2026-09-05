#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int count;
    int value;
} RLEPair;

RLEPair* modified_run_length_encode(const int* list, int size, int* out_size) {
    if (list == NULL || out_size == NULL || size <= 0) {
        if (out_size != NULL) *out_size = 0;
        return NULL;
    }

    RLEPair* encoded = malloc((size / 2 + 1) * sizeof(RLEPair));
    if (encoded == NULL) {
        *out_size = 0;
        return NULL;
    }

    int rle_idx = 0;
    int i = 0;

    while (i < size) {
        if (list[i] == 0) {
            encoded[rle_idx].count = 1;
            encoded[rle_idx].value = 0;
            rle_idx++;
            i++;
        } else {
            int current = list[i];
            int count = 0;
            while (i < size && list[i] == current) {
                count++;
                i++;
            }
            encoded[rle_idx].count = count;
            encoded[rle_idx].value = current;
            rle_idx++;
        }
    }

    *out_size = rle_idx;
    RLEPair* temp = realloc(encoded, rle_idx * sizeof(RLEPair));
    if (temp != NULL) {
        encoded = temp;
    }

    return encoded;
}

int main() {
    int list[] = {1, 1, 1, 0, 2, 2, 3, 0, 0, 4, 4, 4, 4};
    int size = sizeof(list) / sizeof(list[0]);
    int out_size = 0;

    RLEPair* encoded = modified_run_length_encode(list, size, &out_size);

    if (encoded != NULL) {
        for (int i = 0; i < out_size; i++) {
            printf("(%d, %d) ", encoded[i].count, encoded[i].value);
        }
        printf("\n");
        free(encoded);
    }

    return 0;
}