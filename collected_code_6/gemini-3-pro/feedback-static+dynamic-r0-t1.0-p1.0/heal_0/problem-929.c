#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int *elements;
    size_t size;
};

struct ItemCount {
    int item;
    int count;
};

struct CountResult {
    struct ItemCount *counts;
    size_t size;
};

struct CountResult count_repeated_items(const struct Tuple *tuple) {
    struct CountResult result = {NULL, 0};

    if (!tuple || !tuple->elements || tuple->size == 0) {
        return result;
    }

    result.counts = (struct ItemCount *)malloc(tuple->size * sizeof(struct ItemCount));
    if (!result.counts) {
        return result;
    }

    result.size = 0;

    for (size_t i = 0; i < tuple->size; i++) {
        int current_item = tuple->elements[i];
        int found = 0;

        for (size_t j = 0; j < result.size; j++) {
            if (result.counts[j].item == current_item) {
                result.counts[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            result.counts[result.size].item = current_item;
            result.counts[result.size].count = 1;
            result.size++;
        }
    }

    return result;
}

int main(void) {
    int data[] = {1, 2, 2, 3, 4, 4, 4, 5, 1};
    size_t size = sizeof(data) / sizeof(data[0]);

    struct Tuple t = {data, size};

    struct CountResult res = count_repeated_items(&t);

    if (res.counts) {
        for (size_t i = 0; i < res.size; i++) {
            printf("Item: %d, Count: %d\n", res.counts[i].item, res.counts[i].count);
        }
        free(res.counts);
    }

    return 0;
}