#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int count;
    char value;
} RLE_Element;

char* decode_rle(const RLE_Element* encoded, size_t length) {
    if (!encoded && length > 0) {
        return NULL;
    }
    
    if (length == 0) {
        char* empty_str = malloc(1);
        if (empty_str) {
            empty_str[0] = '\0';
        }
        return empty_str;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < length; ++i) {
        if (encoded[i].count < 0) {
            return NULL;
        }
        if (SIZE_MAX - total_length < (size_t)encoded[i].count) {
            return NULL;
        }
        total_length += (size_t)encoded[i].count;
    }

    if (SIZE_MAX - total_length < 1) {
        return NULL;
    }

    char* decoded = malloc(total_length + 1);
    if (!decoded) {
        return NULL;
    }

    size_t pos = 0;
    for (size_t i = 0; i < length; ++i) {
        for (int j = 0; j < encoded[i].count; ++j) {
            decoded[pos++] = encoded[i].value;
        }
    }
    decoded[pos] = '\0';

    return decoded;
}

int main(void) {
    RLE_Element encoded_data[] = {
        {4, 'A'},
        {1, 'B'},
        {2, 'C'},
        {2, 'A'},
        {1, 'D'},
        {4, 'E'}
    };
    
    size_t elements_count = sizeof(encoded_data) / sizeof(encoded_data[0]);

    char* decoded_data = decode_rle(encoded_data, elements_count);
    if (decoded_data) {
        printf("%s\n", decoded_data);
        free(decoded_data);
    } else {
        fprintf(stderr, "Error decoding RLE data\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}