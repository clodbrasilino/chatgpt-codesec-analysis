#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int count;
    int value;
} RLEPair;

RLEPair* modified_run_length_encode(int* list, int size, int* out_size) {
    if (list == NULL || out_size == NULL || size <= 0) {
        if (out_size != NULL) *out_size = 0;
        return NULL;
    }

    RLEPair* encoded = malloc(size * sizeof(RLEPair));
    if (encoded == NULL) {
        *out_size = 0;
        return NULL;
    }

    int current_count = 1;
    int rle_index = 0;

    for (int i = 1; i <= size; i++) {
        if (i < size && list[i] == list[i - 1]) {
            current_count++;
        } else {
            if (current_count > 1) {
                encoded[rle_index].count = current_count;
                encoded[rle_index].value = list[i - 1];
                rle_index++;
            }
            encoded[rle_index].count = 1;
            encoded[rle_index].value = list[i - 1];
            rle_index++;
            current_count = 1;
        }
    }

    RLEPair* final_encoded = realloc(encoded, rle_index * sizeof(RLEPair));
    if (final_encoded != NULL) {
        encoded = final_encoded;
    }

    *out_size = rle_index;
    return encoded;
}

int main() {
    int list[] = {1, 1, 1, 2, 3, 3, 4, 4, 4, 4, 5};
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