#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char character;
    int count;
} RLE_Pair;

char* decode_rle(const RLE_Pair* rle_list, size_t list_size) {
    if (rle_list == NULL || list_size == 0) {
        return NULL;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < list_size; ++i) {
        if (rle_list[i].count < 0) {
            return NULL;
        }
        size_t new_length = total_length + (size_t)rle_list[i].count;
        if (new_length < total_length) {
            return NULL; 
        }
        total_length = new_length;
    }

    char* decoded_string = (char*)malloc(total_length + 1);
    if (decoded_string == NULL) {
        return NULL;
    }

    size_t current_pos = 0;
    for (size_t i = 0; i < list_size; ++i) {
        for (int j = 0; j < rle_list[i].count; ++j) {
            decoded_string[current_pos++] = rle_list[i].character;
        }
    }

    decoded_string[total_length] = '\0';
    return decoded_string;
}

int main(void) {
    RLE_Pair rle_list[] = {
        {'A', 3},
        {'B', 2},
        {'C', 1},
        {'A', 4}
    };
    size_t list_size = sizeof(rle_list) / sizeof(rle_list[0]);

    char* result = decode_rle(rle_list, list_size);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Failed to decode RLE list.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}