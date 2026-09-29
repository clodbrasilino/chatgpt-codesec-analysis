#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int count;
    char character;
} RLEItem;

typedef struct {
    char *data;
    size_t length;
} DecodedString;

DecodedString decode_rle(const RLEItem *items, size_t num_items) {
    DecodedString result = {NULL, 0};
    size_t total_length = 0;

    if (!items || num_items == 0) {
        return result;
    }

    for (size_t i = 0; i < num_items; i++) {
        if (items[i].count > 0) {
            total_length += (size_t)items[i].count;
        } else if (items[i].count == 0) {
            total_length += 1;
        }
    }

    result.data = (char *)malloc(total_length + 1);
    if (!result.data) {
        return result;
    }

    size_t current_pos = 0;
    for (size_t i = 0; i < num_items; i++) {
        int repeat = items[i].count > 0 ? items[i].count : 1;
        for (int j = 0; j < repeat; j++) {
            result.data[current_pos++] = items[i].character;
        }
    }

    result.data[current_pos] = '\0';
    result.length = total_length;

    return result;
}

int main(void) {
    RLEItem encoded_data[] = {
        {4, 'a'},
        {0, 'b'},
        {2, 'c'},
        {2, 'a'},
        {1, 'd'},
        {4, 'e'}
    };
    
    size_t num_items = sizeof(encoded_data) / sizeof(encoded_data[0]);

    DecodedString decoded = decode_rle(encoded_data, num_items);

    if (decoded.data) {
        printf("%s\n", decoded.data);
        free(decoded.data);
    } else {
        fprintf(stderr, "Memory allocation failed or empty input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}