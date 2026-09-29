#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    size_t count;
    int value;
} RlePair;

typedef struct {
    int *data;
    size_t length;
} DecodedList;

DecodedList decode_rle(const RlePair *encoded_list, size_t list_size);

DecodedList decode_rle(const RlePair *encoded_list, size_t list_size) {
    DecodedList result = {NULL, 0};

    if (encoded_list == NULL && list_size > 0) {
        return result;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < list_size; ++i) {
        if (encoded_list[i].count > SIZE_MAX - total_length) {
            return result;
        }
        total_length += encoded_list[i].count;
    }

    if (total_length == 0) {
        return result;
    }

    if (total_length > SIZE_MAX / sizeof(int)) {
        return result;
    }

    result.data = (int *)malloc(total_length * sizeof(int));
    if (result.data == NULL) {
        return result;
    }

    size_t current_index = 0;
    for (size_t i = 0; i < list_size; ++i) {
        for (size_t j = 0; j < encoded_list[i].count; ++j) {
            result.data[current_index++] = encoded_list[i].value;
        }
    }

    result.length = total_length;
    return result;
}

int main(void) {
    RlePair encoded[] = {
        {3, 10},
        {1, 20},
        {4, 30},
        {0, 40},
        {2, 50}
    };
    size_t encoded_size = sizeof(encoded) / sizeof(encoded[0]);

    DecodedList decoded = decode_rle(encoded, encoded_size);

    if (decoded.data != NULL) {
        for (size_t i = 0; i < decoded.length; ++i) {
            printf("%d ", decoded.data[i]);
        }
        printf("\n");
        
        free(decoded.data);
        decoded.data = NULL;
    } else if (encoded_size > 0 && decoded.length == 0) {
        fprintf(stderr, "Error decoding list.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}