#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    SINGLE,
    RUN
} ItemType;

typedef struct {
    ItemType type;
    size_t count;
    int value;
} RLEItem;

int modified_rle(const int *list, size_t length, RLEItem **encoded_list, size_t *encoded_length) {
    if (list == NULL || encoded_list == NULL || encoded_length == NULL) {
        return -1;
    }

    if (length == 0) {
        *encoded_list = NULL;
        *encoded_length = 0;
        return 0;
    }

    if (length > SIZE_MAX / sizeof(RLEItem)) {
        return -1;
    }

    RLEItem *result = malloc(length * sizeof(RLEItem));
    if (result == NULL) {
        return -1;
    }

    size_t out_length = 0;
    size_t i = 0;
    while (i < length) {
        size_t count = 1;
        while (count < length - i && list[i + count] == list[i]) {
            count++;
        }

        if (count > 1) {
            result[out_length].type = RUN;
            result[out_length].count = count;
        } else {
            result[out_length].type = SINGLE;
            result[out_length].count = 1;
        }
        result[out_length].value = list[i];
        
        out_length++;
        i += count;
    }

    if (out_length < length) {
        RLEItem *shrunk = realloc(result, out_length * sizeof(RLEItem));
        if (shrunk != NULL) {
            result = shrunk;
        }
    }

    *encoded_list = result;
    *encoded_length = out_length;
    return 0;
}

int main() {
    int list[] = {1, 1, 1, 2, 3, 3, 4, 4, 4, 4, 5};
    size_t length = sizeof(list) / sizeof(list[0]);
    RLEItem *encoded_list = NULL;
    size_t encoded_length = 0;

    int status = modified_rle(list, length, &encoded_list, &encoded_length);
    
    if (status == 0) {
        for (size_t i = 0; i < encoded_length; i++) {
            if (encoded_list[i].type == RUN) {
                printf("(%zu, %d) ", encoded_list[i].count, encoded_list[i].value);
            } else {
                printf("%d ", encoded_list[i].value);
            }
        }
        printf("\n");
        free(encoded_list);
    } else {
        printf("Encoding failed.\n");
    }

    return 0;
}