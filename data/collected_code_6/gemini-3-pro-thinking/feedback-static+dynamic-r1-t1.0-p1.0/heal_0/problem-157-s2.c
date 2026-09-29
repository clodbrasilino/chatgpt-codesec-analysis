#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct RLEPair {
    size_t count;
    int value;
};

int* decode_rle(const struct RLEPair *encoded_list, size_t encoded_length, size_t *decoded_length) {
    if (!encoded_list || !decoded_length) {
        return NULL;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < encoded_length; ++i) {
        if (SIZE_MAX - total_length < encoded_list[i].count) {
            return NULL;
        }
        total_length += encoded_list[i].count;
    }

    *decoded_length = total_length;

    if (total_length == 0) {
        return NULL;
    }

    if (SIZE_MAX / sizeof(int) < total_length) {
        return NULL;
    }

    int *decoded_list = (int *)malloc(total_length * sizeof(int));
    if (!decoded_list) {
        return NULL;
    }

    size_t current_index = 0;
    for (size_t i = 0; i < encoded_length; ++i) {
        for (size_t j = 0; j < encoded_list[i].count; ++j) {
            decoded_list[current_index++] = encoded_list[i].value;
        }
    }

    return decoded_list;
}

int main(void) {
    struct RLEPair encoded_data[] = {
        {3, 10},
        {1, 20},
        {4, 30}
    };
    
    size_t encoded_length = sizeof(encoded_data) / sizeof(encoded_data[0]);
    size_t decoded_length = 0;

    int *decoded_data = decode_rle(encoded_data, encoded_length, &decoded_length);

    if (decoded_data) {
        for (size_t i = 0; i < decoded_length; ++i) {
            printf("%d ", decoded_data[i]);
        }
        printf("\n");
        
        free(decoded_data);
        decoded_data = NULL;
    }

    return 0;
}