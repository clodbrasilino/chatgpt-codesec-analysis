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

RLEList* rle_encode(const int *list, size_t size) {
    RLEList *rle = malloc(sizeof(RLEList));
    if (!rle) return NULL;

    rle->capacity = size > 0 ? size : 1;
    rle->data = malloc(rle->capacity * sizeof(RLEPair));
    if (!rle->data) {
        free(rle);
        return NULL;
    }
    rle->length = 0;

    if (size == 0) return rle;

    int current = list[0];
    int count = 1;

    for (size_t i = 1; i < size; i++) {
        if (list[i] == current) {
            count++;
        } else {
            rle->data[rle->length].count = count;
            rle->data[rle->length].value = current;
            rle->length++;
            current = list[i];
            count = 1;
        }
    }

    rle->data[rle->length].count = count;
    rle->data[rle->length].value = current;
    rle->length++;

    return rle;
}

RLEList* rle_encode_modified(const int *list, size_t size) {
    RLEList *rle = malloc(sizeof(RLEList));
    if (!rle) return NULL;

    rle->capacity = size > 0 ? size : 1;
    rle->data = malloc(rle->capacity * sizeof(RLEPair));
    if (!rle->data) {
        free(rle);
        return NULL;
    }
    rle->length = 0;

    if (size == 0) return rle;

    int current = list[0];
    int count = 1;

    for (size_t i = 1; i < size; i++) {
        if (list[i] == current) {
            count++;
        } else {
            if (count == 1) {
                rle->data[rle->length].count = 1;
                rle->data[rle->length].value = current;
                rle->length++;
            } else {
                rle->data[rle->length].count = count;
                rle->data[rle->length].value = current;
                rle->length++;
            }
            current = list[i];
            count = 1;
        }
    }

    if (count == 1) {
        rle->data[rle->length].count = 1;
        rle->data[rle->length].value = current;
        rle->length++;
    } else {
        rle->data[rle->length].count = count;
        rle->data[rle->length].value = current;
        rle->length++;
    }

    return rle;
}

void rle_free(RLEList *rle) {
    if (rle) {
        free(rle->data);
        free(rle);
    }
}

int main(void) {
    int list[] = {1, 1, 1, 2, 3, 3, 4, 5, 5, 5, 5, 6};
    size_t size = sizeof(list) / sizeof(list[0]);

    RLEList *standard = rle_encode(list, size);
    if (!standard) {
        fprintf(stderr, "Memory allocation failed for standard encoding\n");
        return 1;
    }

    printf("Standard RLE:\n");
    for (size_t i = 0; i < standard->length; i++) {
        printf("(%d, %d) ", standard->data[i].count, standard->data[i].value);
    }
    printf("\n");

    RLEList *modified = rle_encode_modified(list, size);
    if (!modified) {
        fprintf(stderr, "Memory allocation failed for modified encoding\n");
        rle_free(standard);
        return 1;
    }

    printf("Modified RLE:\n");
    for (size_t i = 0; i < modified->length; i++) {
        printf("(%d, %d) ", modified->data[i].count, modified->data[i].value);
    }
    printf("\n");

    rle_free(standard);
    rle_free(modified);

    return 0;
}