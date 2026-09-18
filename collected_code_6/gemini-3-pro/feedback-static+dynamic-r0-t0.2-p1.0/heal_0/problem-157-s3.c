#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} RLEPair;

int* decode_rle(const RLEPair* encoded_list, size_t list_size, size_t* decoded_size) {
    if (encoded_list == NULL || decoded_size == NULL) {
        return NULL;
    }

    size_t total_elements = 0;
    for (size_t i = 0; i < list_size; ++i) {
        if (encoded_list[i].count < 0) {
            return NULL;
        }
        total_elements += (size_t)encoded_list[i].count;
    }

    int* decoded_list = (int*)malloc(total_elements * sizeof(int));
    if (decoded_list == NULL) {
        return NULL;
    }

    size_t current_index = 0;
    for (size_t i = 0; i < list_size; ++i) {
        for (int j = 0; j < encoded_list[i].count; ++j) {
            decoded_list[current_index++] = encoded_list[i].value;
        }
    }

    *decoded_size = total_elements;
    return decoded_list;
}

int main(void) {
    RLEPair encoded_data[] = {
        {5, 3},
        {2, 1},
        {8, 4},
        {1, 2}
    };
    size_t encoded_size = sizeof(encoded_data) / sizeof(encoded_data[0]);
    size_t decoded_size = 0;

    int* decoded_data = decode_rle(encoded_data, encoded_size, &decoded_size);

    if (decoded_data != NULL) {
        for (size_t i = 0; i < decoded_size; ++i) {
            printf("%d ", decoded_data[i]);
        }
        printf("\n");

        free(decoded_data);
    } else {
        fprintf(stderr, "Failed to decode RLE data.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}