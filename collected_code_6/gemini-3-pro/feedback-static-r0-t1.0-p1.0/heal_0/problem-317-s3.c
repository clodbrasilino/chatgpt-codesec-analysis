#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} RunLengthItem;

void decode_modified_rle(const RunLengthItem* encoded_list, size_t list_size, int** decoded_list, size_t* decoded_size) {
    if (!encoded_list || !decoded_list || !decoded_size) {
        return;
    }

    size_t total_elements = 0;
    for (size_t i = 0; i < list_size; ++i) {
        total_elements += encoded_list[i].count;
    }

    *decoded_list = (int*)malloc(total_elements * sizeof(int));
    if (!*decoded_list) {
        *decoded_size = 0;
        return;
    }

    *decoded_size = total_elements;

    size_t index = 0;
    for (size_t i = 0; i < list_size; ++i) {
        for (int j = 0; j < encoded_list[i].count; ++j) {
            (*decoded_list)[index++] = encoded_list[i].value;
        }
    }
}

int main(void) {
    RunLengthItem encoded_data[] = {
        {5, 3},
        {12, 1},
        {7, 4}
    };
    size_t encoded_size = sizeof(encoded_data) / sizeof(encoded_data[0]);

    int* decoded_data = NULL;
    size_t decoded_size = 0;

    decode_modified_rle(encoded_data, encoded_size, &decoded_data, &decoded_size);

    if (decoded_data) {
        for (size_t i = 0; i < decoded_size; ++i) {
            printf("%d ", decoded_data[i]);
        }
        printf("\n");
        free(decoded_data);
    } else {
        printf("Decoding failed or empty input.\n");
    }

    return 0;
}