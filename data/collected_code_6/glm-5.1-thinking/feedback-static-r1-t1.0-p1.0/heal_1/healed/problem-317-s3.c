#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t count;
    int value;
} RLE;

RLE* modified_run_length_encode(const int* list, size_t length, size_t* out_length) {
    if (list == NULL || out_length == NULL) {
        return NULL;
    }

    size_t alloc_size = (length > 0 ? length : 1) * sizeof(RLE);
    RLE* encoded = malloc(alloc_size);
    if (encoded == NULL) {
        return NULL;
    }

    size_t j = 0;
    size_t i = 0;

    while (i < length) {
        int current = list[i];
        size_t count = 1;
        while (i + count < length && list[i + count] == current) {
            count++;
        }
        
        encoded[j].count = count;
        encoded[j].value = current;
        j++;
        
        i += count;
    }

    *out_length = j;
    return encoded;
}

int main(void) {
    int list[] = {1, 1, 1, 1, 2, 3, 3, 1, 4, 4, 4, 4, 4};
    size_t length = sizeof(list) / sizeof(list[0]);
    size_t out_length = 0;

    RLE* encoded = modified_run_length_encode(list, length, &out_length);
    if (encoded == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < out_length; i++) {
        if (encoded[i].count > 1) {
            printf("(%zu, %d) ", encoded[i].count, encoded[i].value);
        } else {
            printf("%d ", encoded[i].value);
        }
    }
    printf("\n");

    free(encoded);
    return 0;
}