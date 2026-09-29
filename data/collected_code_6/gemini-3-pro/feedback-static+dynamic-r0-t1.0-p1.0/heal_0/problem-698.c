#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key1;
    int key2;
    int val;
} DictItem;

typedef struct {
    DictItem item;
    long long product;
} SortItem;

int compare_items(const void *a, const void *b) {
    long long prodA = ((SortItem *)a)->product;
    long long prodB = ((SortItem *)b)->product;
    if (prodA < prodB) return -1;
    if (prodA > prodB) return 1;
    return 0;
}

DictItem* sort_dict_by_key_product(const DictItem *dict, size_t size) {
    if (dict == NULL || size == 0) {
        return NULL;
    }

    SortItem *sort_array = (SortItem *)malloc(size * sizeof(SortItem));
    if (sort_array == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        sort_array[i].item = dict[i];
        sort_array[i].product = (long long)dict[i].key1 * dict[i].key2;
    }

    qsort(sort_array, size, sizeof(SortItem), compare_items);

    DictItem *sorted_dict = (DictItem *)malloc(size * sizeof(DictItem));
    if (sorted_dict == NULL) {
        free(sort_array);
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        sorted_dict[i] = sort_array[i].item;
    }

    free(sort_array);
    return sorted_dict;
}

int main() {
    DictItem dict[] = {
        {3, 4, 100},
        {1, 2, 200},
        {5, 6, 300},
        {2, 3, 400}
    };
    size_t size = sizeof(dict) / sizeof(dict[0]);

    DictItem *sorted_dict = sort_dict_by_key_product(dict, size);
    if (sorted_dict == NULL) {
        return 1;
    }

    for (size_t i = 0; i < size; i++) {
        printf("Key: (%d, %d), Value: %d\n", sorted_dict[i].key1, sorted_dict[i].key2, sorted_dict[i].val);
    }

    free(sorted_dict);
    return 0;
}