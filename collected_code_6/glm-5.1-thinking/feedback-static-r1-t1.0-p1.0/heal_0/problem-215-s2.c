#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int* decode_rle(const int* encoded, size_t encoded_len, size_t* decoded_len) {
    if (encoded == NULL || decoded_len == NULL) {
        return NULL;
    }
    if (encoded_len % 2 != 0) {
        return NULL;
    }
    
    size_t total_len = 0;
    for (size_t i = 0; i < encoded_len; i += 2) {
        if (encoded[i] <= 0) {
            return NULL;
        }
        size_t count = (size_t)encoded[i];
        if (count > SIZE_MAX - total_len) {
            return NULL;
        }
        total_len += count;
    }
    
    *decoded_len = total_len;
    
    if (total_len == 0) {
        return NULL;
    }
    
    if (total_len > SIZE_MAX / sizeof(int)) {
        return NULL;
    }
    
    int* decoded = malloc(total_len * sizeof(int));
    if (decoded == NULL) {
        return NULL;
    }
    
    size_t pos = 0;
    for (size_t i = 0; i < encoded_len; i += 2) {
        size_t count = (size_t)encoded[i];
        int value = encoded[i + 1];
        for (size_t j = 0; j < count; j++) {
            decoded[pos++] = value;
        }
    }
    
    return decoded;
}

int main(void) {
    int encoded[] = {3, 10, 2, 5, 1, 8};
    size_t encoded_len = sizeof(encoded) / sizeof(encoded[0]);
    size_t decoded_len = 0;
    
    int* decoded = decode_rle(encoded, encoded_len, &decoded_len);
    
    if (decoded != NULL) {
        for (size_t i = 0; i < decoded_len; i++) {
            printf("%d ", decoded[i]);
        }
        printf("\n");
        free(decoded);
    } else {
        if (decoded_len == 0) {
            printf("Decoded array is empty.\n");
        } else {
            printf("Decoding failed due to invalid input or memory allocation error.\n");
        }
    }
    
    return 0;
}