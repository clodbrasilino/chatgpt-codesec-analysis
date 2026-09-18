#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int count;
    char value;
} RLEPair;

typedef struct {
    char *data;
    size_t length;
} DecodedList;

DecodedList decode_rle(const RLEPair *encoded_list, size_t list_size) {
    DecodedList result = {NULL, 0};
    size_t total_length = 0;

    if (encoded_list == NULL || list_size == 0) {
        return result;
    }

    for (size_t i = 0; i < list_size; ++i) {
        if (encoded_list[i].count < 0) {
            return result;
        }
        total_length += (size_t)encoded_list[i].count;
    }

    result.data = (char *)malloc(total_length + 1);
    if (result.data == NULL) {
        return result;
    }

    size_t current_index = 0;
    for (size_t i = 0; i < list_size; ++i) {
        for (int j = 0; j < encoded_list[i].count; ++j) {
            result.data[current_index++] = encoded_list[i].value;
        }
    }
    
    result.data[total_length] = '\0';
    result.length = total_length;

    return result;
}

int main(void) {
    RLEPair encoded[] = {
        {3, 'A'},
        {2, 'B'},
        {5, 'C'},
        {1, 'D'}
    };
    size_t list_size = sizeof(encoded) / sizeof(encoded[0]);

    DecodedList decoded = decode_rle(encoded, list_size);

    if (decoded.data != NULL) {
        printf("%s\n", decoded.data);
        free(decoded.data);
    } else {
        fprintf(stderr, "Failed to decode the list.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}