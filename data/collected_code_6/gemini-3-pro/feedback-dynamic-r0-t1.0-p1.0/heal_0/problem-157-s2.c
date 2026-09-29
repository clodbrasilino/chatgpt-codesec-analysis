#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} RLEElement;

int* decode_rle(const RLEElement* encoded_list, size_t list_size, size_t* out_size) {
    if (!encoded_list || !out_size) {
        return NULL;
    }

    size_t total_size = 0;
    for (size_t i = 0; i < list_size; ++i) {
        if (encoded_list[i].count < 0) {
            return NULL;
        }
        total_size += (size_t)encoded_list[i].count;
    }

    int* decoded_array = (int*)malloc(total_size * sizeof(int));
    if (!decoded_array) {
        return NULL;
    }

    size_t current_index = 0;
    for (size_t i = 0; i < list_size; ++i) {
        for (int j = 0; j < encoded_list[i].count; ++j) {
            decoded_array[current_index++] = encoded_list[i].value;
        }
    }

    *out_size = total_size;
    return decoded_array;
}

int main(void) {
    RLEElement encoded_list[] = {
        {1, 3},
        {2, 1},
        {3, 4},
        {4, 2}
    };
    size_t list_size = sizeof(encoded_list) / sizeof(encoded_list[0]);
    size_t decoded_size = 0;

    int* decoded_array = decode_rle(encoded_list, list_size, &decoded_size);

    if (decoded_array) {
        for (size_t i = 0; i < decoded_size; ++i) {
            printf("%d ", decoded_array[i]);
        }
        printf("\n");
        free(decoded_array);
    } else {
        printf("Decoding failed.\n");
    }

    return 0;
}