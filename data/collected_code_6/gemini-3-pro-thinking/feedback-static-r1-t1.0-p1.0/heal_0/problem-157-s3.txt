#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
    size_t count;
    char character;
} RLEPair;

char* decode_rle(const RLEPair* pairs, size_t num_pairs) {
    if (!pairs && num_pairs > 0) {
        return NULL;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < num_pairs; i++) {
        if (SIZE_MAX - total_length < pairs[i].count) {
            return NULL;
        }
        total_length += pairs[i].count;
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    char* decoded_string = (char*)malloc(total_length + 1);
    if (!decoded_string) {
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < num_pairs; i++) {
        for (size_t j = 0; j < pairs[i].count; j++) {
            decoded_string[index++] = pairs[i].character;
        }
    }
    decoded_string[total_length] = '\0';

    return decoded_string;
}

int main(void) {
    RLEPair encoded_data[] = {
        {3, 'A'},
        {2, 'B'},
        {5, 'C'},
        {1, 'D'}
    };
    
    size_t num_pairs = sizeof(encoded_data) / sizeof(encoded_data[0]);

    char* result = decode_rle(encoded_data, num_pairs);
    if (!result) {
        fprintf(stderr, "Error: memory allocation or overflow failure during RLE decoding.\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}