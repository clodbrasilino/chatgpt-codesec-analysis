#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    size_t count;
    int value;
} RLEPair;

typedef struct {
    int *data;
    size_t length;
} DecodedList;

DecodedList decode_rle(const RLEPair *encoded, size_t num_pairs) {
    DecodedList result = {NULL, 0};

    if (!encoded && num_pairs > 0) {
        return result;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < num_pairs; i++) {
        if (encoded[i].count > SIZE_MAX - total_length) {
            return result;
        }
        total_length += encoded[i].count;
    }

    if (total_length == 0) {
        return result;
    }

    if (total_length > SIZE_MAX / sizeof(int)) {
        return result;
    }

    result.data = (int *)malloc(total_length * sizeof(int));
    if (!result.data) {
        return result;
    }

    result.length = total_length;

    size_t current_index = 0;
    for (size_t i = 0; i < num_pairs; i++) {
        for (size_t j = 0; j < encoded[i].count; j++) {
            result.data[current_index++] = encoded[i].value;
        }
    }

    return result;
}

int main(void) {
    RLEPair encoded_data[] = {
        {3, 10},
        {1, 25},
        {4, 7}
    };
    /* Possible weaknesses found:
     *  Assignment 'num_pairs=sizeof(encoded_data)/sizeof(encoded_data[0])', assigned value is 3
     */
    size_t num_pairs = sizeof(encoded_data) / sizeof(encoded_data[0]);

    DecodedList decoded = decode_rle(encoded_data, num_pairs);

    if (decoded.data != NULL) {
        for (size_t i = 0; i < decoded.length; i++) {
            printf("%d ", decoded.data[i]);
        }
        printf("\n");

        free(decoded.data);
    /* Possible weaknesses found:
     *  Condition 'num_pairs>0' is always true [knownConditionTrueFalse]
     *  Condition 'num_pairs>0' is always true
     */
    } else if (decoded.length == 0 && num_pairs > 0) {
        fprintf(stderr, "Failed to decode RLE list.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}