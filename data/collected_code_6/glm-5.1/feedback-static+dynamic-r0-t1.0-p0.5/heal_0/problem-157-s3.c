#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} RLEPair;

typedef struct {
    RLEPair *pairs;
    size_t size;
} RLEList;

RLEList* rle_encode(const int *data, size_t data_size) {
    if (data == NULL) {
        return NULL;
    }

    RLEList *list = (RLEList*)malloc(sizeof(RLEList));
    if (list == NULL) {
        return NULL;
    }

    if (data_size == 0) {
        list->pairs = NULL;
        list->size = 0;
        return list;
    }

    list->pairs = (RLEPair*)malloc(data_size * sizeof(RLEPair));
    if (list->pairs == NULL) {
        free(list);
        return NULL;
    }

    size_t rle_index = 0;
    list->pairs[0].value = data[0];
    list->pairs[0].count = 1;

    for (size_t i = 1; i < data_size; ++i) {
        if (data[i] == list->pairs[rle_index].value) {
            list->pairs[rle_index].count++;
        } else {
            rle_index++;
            list->pairs[rle_index].value = data[i];
            list->pairs[rle_index].count = 1;
        }
    }

    list->size = rle_index + 1;

    RLEPair *temp = (RLEPair*)realloc(list->pairs, list->size * sizeof(RLEPair));
    if (temp != NULL) {
        list->pairs = temp;
    }

    return list;
}

void rle_free(RLEList *list) {
    if (list != NULL) {
        free(list->pairs);
        free(list);
    }
}

int main(void) {
    int data[] = {1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5};
    size_t data_size = sizeof(data) / sizeof(data[0]);

    RLEList *encoded = rle_encode(data, data_size);
    if (encoded == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < encoded->size; ++i) {
        printf("%d: %zu\n", encoded->pairs[i].value, encoded->pairs[i].count);
    }

    rle_free(encoded);

    return EXIT_SUCCESS;
}