#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int count;
    char character;
} RLEItem;

typedef struct {
    RLEItem* items;
    size_t size;
    size_t capacity;
} RLEList;

RLEList* create_rle_list(size_t initial_capacity) {
    if (initial_capacity == 0) {
        return NULL;
    }

    RLEList* list = (RLEList*)malloc(sizeof(RLEList));
    if (!list) {
        return NULL;
    }

    list->items = (RLEItem*)malloc(initial_capacity * sizeof(RLEItem));
    if (!list->items) {
        free(list);
        return NULL;
    }

    list->size = 0;
    list->capacity = initial_capacity;
    return list;
}

void free_rle_list(RLEList* list) {
    if (list) {
        free(list->items);
        free(list);
    }
}

int add_rle_item(RLEList* list, int count, char character) {
    if (!list) {
        return -1;
    }

    if (list->size >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        RLEItem* new_items = (RLEItem*)realloc(list->items, new_capacity * sizeof(RLEItem));
        if (!new_items) {
            return -1;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }

    list->items[list->size].count = count;
    list->items[list->size].character = character;
    list->size++;
    return 0;
}

char* decode_rle_list(const RLEList* list) {
    if (!list) {
        return NULL;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < list->size; i++) {
        if (list->items[i].count < 0) {
            return NULL;
        }
        total_length += (size_t)list->items[i].count;
    }

    char* decoded_string = (char*)malloc((total_length + 1) * sizeof(char));
    if (!decoded_string) {
        return NULL;
    }

    size_t current_pos = 0;
    for (size_t i = 0; i < list->size; i++) {
        int count = list->items[i].count;
        char character = list->items[i].character;
        for (int j = 0; j < count; j++) {
            decoded_string[current_pos++] = character;
        }
    }

    decoded_string[total_length] = '\0';
    return decoded_string;
}

int main(void) {
    RLEList* list = create_rle_list(4);
    if (!list) {
        fprintf(stderr, "Failed to create RLE list\n");
        return 1;
    }

    if (add_rle_item(list, 4, 'A') != 0 ||
        add_rle_item(list, 1, 'B') != 0 ||
        add_rle_item(list, 3, 'C') != 0 ||
        add_rle_item(list, 2, 'A') != 0) {
        fprintf(stderr, "Failed to add items to RLE list\n");
        free_rle_list(list);
        return 1;
    }

    char* decoded = decode_rle_list(list);
    if (decoded) {
        printf("Decoded string: %s\n", decoded);
        free(decoded);
    } else {
        fprintf(stderr, "Failed to decode RLE list\n");
    }

    free_rle_list(list);
    return 0;
}