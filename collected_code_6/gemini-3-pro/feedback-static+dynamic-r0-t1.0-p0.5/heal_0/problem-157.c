#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} RLEPair;

int* decode_rle(const RLEPair* rle_list, size_t list_size, size_t* out_size) {
    if (!rle_list || !out_size) {
        return NULL;
    }

    size_t total_elements = 0;
    for (size_t i = 0; i < list_size; ++i) {
        if (rle_list[i].count < 0) {
            return NULL;
        }
        total_elements += (size_t)rle_list[i].count;
    }

    int* decoded_array = (int*)malloc(total_elements * sizeof(int));
    if (!decoded_array) {
        return NULL;
    }

    size_t current_index = 0;
    for (size_t i = 0; i < list_size; ++i) {
        for (int j = 0; j < rle_list[i].count; ++j) {
            decoded_array[current_index++] = rle_list[i].value;
        }
    }

    *out_size = total_elements;
    return decoded_array;
}

int main(void) {
    RLEPair rle_data[] = {
        {5, 3},
        {2, 1},
        {8, 4},
        {1, 2}
    };
    size_t rle_size = sizeof(rle_data) / sizeof(rle_data[0]);
    size_t decoded_size = 0;

    int* decoded = decode_rle(rle_data, rle_size, &decoded_size);

    if (decoded) {
        for (size_t i = 0; i < decoded_size; ++i) {
            printf("%d ", decoded[i]);
        }
        printf("\n");
        free(decoded);
    } else {
        fprintf(stderr, "Failed to decode RLE data.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}