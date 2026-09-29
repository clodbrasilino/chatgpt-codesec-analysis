#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    RLE_SINGLE,
    RLE_RUN
} RLEItemType;

typedef struct {
    RLEItemType type;
    int value;
    size_t count;
} RLEItem;

int *reflect_modified_run_length_encoding(const RLEItem *items, size_t item_count, size_t *decoded_count) {
    if (decoded_count == NULL) {
        return NULL;
    }
    if (item_count == 0) {
        *decoded_count = 0;
        return NULL;
    }
    if (items == NULL) {
        *decoded_count = 0;
        return NULL;
    }

    size_t total = 0;
    for (size_t i = 0; i < item_count; ++i) {
        if (items[i].type == RLE_RUN) {
            if (items[i].count < 2) {
                *decoded_count = 0;
                return NULL;
            }
            if (items[i].count > SIZE_MAX - total) {
                *decoded_count = 0;
                return NULL;
            }
            total += items[i].count;
        } else if (items[i].type == RLE_SINGLE) {
            if (total == SIZE_MAX) {
                *decoded_count = 0;
                return NULL;
            }
            total += 1;
        } else {
            *decoded_count = 0;
            return NULL;
        }
    }

    if (total > SIZE_MAX / sizeof(int)) {
        *decoded_count = 0;
        return NULL;
    }

    int *decoded = malloc(total * sizeof(int));
    if (decoded == NULL) {
        *decoded_count = 0;
        return NULL;
    }

    size_t position = 0;
    for (size_t i = 0; i < item_count; ++i) {
        if (items[i].type == RLE_RUN) {
            for (size_t j = 0; j < items[i].count; ++j) {
                decoded[position++] = items[i].value;
            }
        } else {
            decoded[position++] = items[i].value;
        }
    }

    *decoded_count = total;
    return decoded;
}

int main(void) {
    RLEItem encoded[] = {
        { RLE_RUN, 1, 3 },
        { RLE_SINGLE, 2, 0 },
        { RLE_RUN, 3, 2 }
    };
    size_t decoded_count = 0;
    int *decoded = reflect_modified_run_length_encoding(encoded, sizeof(encoded) / sizeof(encoded[0]), &decoded_count);
    if (decoded != NULL) {
        for (size_t i = 0; i < decoded_count; ++i) {
            printf("%d ", decoded[i]);
        }
        printf("\n");
        free(decoded);
    }
    return 0;
}