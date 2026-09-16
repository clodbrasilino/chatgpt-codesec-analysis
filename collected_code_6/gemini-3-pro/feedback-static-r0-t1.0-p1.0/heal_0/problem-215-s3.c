#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} RLEPair;

typedef struct {
    int* data;
    size_t length;
    size_t capacity;
} IntegerList;

IntegerList* create_list(size_t capacity) {
    if (capacity == 0) return NULL;
    IntegerList* list = (IntegerList*)malloc(sizeof(IntegerList));
    if (!list) return NULL;
    list->data = (int*)malloc(capacity * sizeof(int));
    if (!list->data) {
        free(list);
        return NULL;
    }
    list->length = 0;
    list->capacity = capacity;
    return list;
}

void free_list(IntegerList* list) {
    if (list) {
        free(list->data);
        free(list);
    }
}

int append_to_list(IntegerList* list, int value) {
    if (!list || !list->data) return -1;
    if (list->length >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        int* new_data = (int*)realloc(list->data, new_capacity * sizeof(int));
        if (!new_data) return -1;
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->length++] = value;
    return 0;
}

IntegerList* decode_rle(const RLEPair* encoded_list, size_t num_pairs) {
    if (!encoded_list) return NULL;
    
    size_t initial_capacity = 16;
    IntegerList* decoded_list = create_list(initial_capacity);
    if (!decoded_list) return NULL;

    for (size_t i = 0; i < num_pairs; ++i) {
        if (encoded_list[i].count < 0) {
            free_list(decoded_list);
            return NULL;
        }
        for (int j = 0; j < encoded_list[i].count; ++j) {
            if (append_to_list(decoded_list, encoded_list[i].value) != 0) {
                free_list(decoded_list);
                return NULL;
            }
        }
    }
    return decoded_list;
}

int main(void) {
    RLEPair encoded[] = {
        {1, 3},
        {2, 1},
        {5, 4},
        {9, 0},
        {3, 2}
    };
    size_t num_pairs = sizeof(encoded) / sizeof(encoded[0]);

    IntegerList* decoded = decode_rle(encoded, num_pairs);
    if (!decoded) {
        fprintf(stderr, "Failed to decode list.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < decoded->length; ++i) {
        printf("%d ", decoded->data[i]);
    }
    printf("\n");

    free_list(decoded);
    return EXIT_SUCCESS;
}