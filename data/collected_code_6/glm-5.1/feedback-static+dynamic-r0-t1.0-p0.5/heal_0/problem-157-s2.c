#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} RLE;

int rle_encode(const int *input, size_t input_len, RLE **output, size_t *output_len) {
    if (input == NULL || output == NULL || output_len == NULL) {
        return -1;
    }

    *output = NULL;
    *output_len = 0;

    if (input_len == 0) {
        return 0;
    }

    size_t capacity = 16;
    *output = (RLE *)malloc(capacity * sizeof(RLE));
    if (*output == NULL) {
        return -1;
    }

    size_t out_idx = 0;
    int current_val = input[0];
    size_t current_count = 1;

    for (size_t i = 1; i < input_len; i++) {
        if (input[i] == current_val) {
            current_count++;
        } else {
            if (out_idx >= capacity) {
                capacity *= 2;
                RLE *temp = (RLE *)realloc(*output, capacity * sizeof(RLE));
                if (temp == NULL) {
                    free(*output);
                    *output = NULL;
                    *output_len = 0;
                    return -1;
                }
                *output = temp;
            }
            (*output)[out_idx].value = current_val;
            (*output)[out_idx].count = current_count;
            out_idx++;

            current_val = input[i];
            current_count = 1;
        }
    }

    if (out_idx >= capacity) {
        capacity += 1;
        RLE *temp = (RLE *)realloc(*output, capacity * sizeof(RLE));
        if (temp == NULL) {
            free(*output);
            *output = NULL;
            *output_len = 0;
            return -1;
        }
        *output = temp;
    }
    (*output)[out_idx].value = current_val;
    (*output)[out_idx].count = current_count;
    out_idx++;

    *output_len = out_idx;

    return 0;
}

int main(void) {
    int data[] = {1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5};
    size_t data_len = sizeof(data) / sizeof(data[0]);

    RLE *encoded = NULL;
    size_t encoded_len = 0;

    if (rle_encode(data, data_len, &encoded, &encoded_len) == 0) {
        for (size_t i = 0; i < encoded_len; i++) {
            printf("%d:%zu ", encoded[i].value, encoded[i].count);
        }
        printf("\n");
        free(encoded);
    }

    return 0;
}