#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int count;
    char character;
} RLEItem;

typedef struct {
    RLEItem* items;
    size_t size;
} RLEList;

char* decode_rle(const RLEList* list) {
    if (!list || !list->items) {
        return NULL;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < list->size; ++i) {
        if (list->items[i].count < 0) {
            return NULL;
        }
        total_length += (size_t)list->items[i].count;
    }

    char* decoded_string = (char*)malloc(total_length + 1);
    if (!decoded_string) {
        return NULL;
    }

    size_t current_pos = 0;
    for (size_t i = 0; i < list->size; ++i) {
        int count = list->items[i].count;
        char character = list->items[i].character;
        for (int j = 0; j < count; ++j) {
            decoded_string[current_pos++] = character;
        }
    }

    decoded_string[total_length] = '\0';
    return decoded_string;
}

int main(void) {
    RLEItem items[] = {
        {4, 'A'},
        {1, 'B'},
        {3, 'C'},
        {2, 'A'}
    };
    
    RLEList list = {items, sizeof(items) / sizeof(items[0])};

    char* decoded = decode_rle(&list);
    if (decoded) {
        printf("%s\n", decoded);
        free(decoded);
    } else {
        fprintf(stderr, "Failed to decode RLE list.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}