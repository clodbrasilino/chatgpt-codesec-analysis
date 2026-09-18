#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    size_t count;
    int value;
} RLE_Pair;

typedef enum {
    SUCCESS = 0,
    ERR_NULL_POINTER = -1,
    ERR_OVERFLOW = -2,
    ERR_ALLOCATION = -3
} RLE_Error;

RLE_Error decode_rle(const RLE_Pair *encoded, size_t encoded_len, int **decoded, size_t *decoded_len) {
    if (!decoded || !decoded_len) {
        return ERR_NULL_POINTER;
    }

    if (encoded_len == 0 || !encoded) {
        *decoded = NULL;
        *decoded_len = 0;
        return SUCCESS;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < encoded_len; ++i) {
        if (total_length > ((size_t)-1) - encoded[i].count) {
            return ERR_OVERFLOW;
        }
        total_length += encoded[i].count;
    }

    if (total_length == 0) {
        *decoded = NULL;
        *decoded_len = 0;
        return SUCCESS;
    }

    if (total_length > ((size_t)-1) / sizeof(int)) {
        return ERR_OVERFLOW;
    }

    int *result = (int *)malloc(total_length * sizeof(int));
    if (!result) {
        return ERR_ALLOCATION;
    }

    size_t index = 0;
    for (size_t i = 0; i < encoded_len; ++i) {
        for (size_t j = 0; j < encoded[i].count; ++j) {
            result[index++] = encoded[i].value;
        }
    }

    *decoded = result;
    *decoded_len = total_length;

    return SUCCESS;
}

int main(void) {
    RLE_Pair encoded_data[] = {
        {3, 10},
        {1, 20},
        {4, 30}
    };
    size_t encoded_len = sizeof(encoded_data) / sizeof(encoded_data[0]);

    int *decoded_data = NULL;
    size_t decoded_len = 0;

    RLE_Error status = decode_rle(encoded_data, encoded_len, &decoded_data, &decoded_len);

    if (status == SUCCESS) {
        for (size_t i = 0; i < decoded_len; ++i) {
            printf("%d ", decoded_data[i]);
        }
        printf("\n");

        free(decoded_data);
        decoded_data = NULL;
    } else {
        fprintf(stderr, "Error decoding RLE data: %d\n", status);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}