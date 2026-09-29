#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int count;
    int value;
} RLEPair;

typedef struct {
    RLEPair *data;
    size_t length;
    size_t capacity;
} RLEList;

RLEList* rle_encode(const int *list, size_t list_len) {
    RLEList *rle = malloc(sizeof(RLEList));
    if (!rle) return NULL;

    rle->capacity = list_len > 0 ? list_len : 1;
    rle->data = malloc(rle->capacity * sizeof(RLEPair));
    if (!rle->data) {
        free(rle);
        return NULL;
    }
    rle->length = 0;

    if (list_len == 0) return rle;

    int current = list[0];
    int count = 1;

    for (size_t i = 1; i < list_len; i++) {
        if (list[i] == current) {
            count++;
        } else {
            if (rle->length >= rle->capacity) {
                size_t new_cap = rle->capacity * 2;
                RLEPair *new_data = realloc(rle->data, new_cap * sizeof(RLEPair));
                if (!new_data) {
                    free(rle->data);
                    free(rle);
                    return NULL;
                }
                rle->data = new_data;
                rle->capacity = new_cap;
            }
            rle->data[rle->length].count = count;
            rle->data[rle->length].value = current;
            rle->length++;
            current = list[i];
            count = 1;
        }
    }

    if (rle->length >= rle->capacity) {
        size_t new_cap = rle->capacity * 2;
        RLEPair *new_data = realloc(rle->data, new_cap * sizeof(RLEPair));
        if (!new_data) {
            free(rle->data);
            free(rle);
            return NULL;
        }
        rle->data = new_data;
        rle->capacity = new_cap;
    }
    rle->data[rle->length].count = count;
    rle->data[rle->length].value = current;
    rle->length++;

    return rle;
}

void rle_free(RLEList *rle) {
    if (rle) {
        free(rle->data);
        free(rle);
    }
}

int main() {
    int list[] = {1, 1, 1, 2, 3, 3, 4, 4, 4, 4, 5};
    size_t len = sizeof(list) / sizeof(list[0]);

    RLEList *rle = rle_encode(list, len);
    if (!rle) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < rle->length; i++) {
        printf("%d:%d ", rle->data[i].count, rle->data[i].value);
    }
    printf("\n");

    rle_free(rle);

    return 0;
}