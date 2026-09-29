#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key[2];
    int value;
    long long product;
} DictItem;

long long tuple_product(const int *key, int size) {
    long long product = 1;
    for (int i = 0; i < size; i++) {
        product *= key[i];
    }
    return product;
}

int compare_dict_items(const void *a, const void *b) {
    const DictItem *item_a = (const DictItem *)a;
    const DictItem *item_b = (const DictItem *)b;
    if (item_a->product < item_b->product) return -1;
    if (item_a->product > item_b->product) return 1;
    return 0;
}

void sort_dictionary_by_tuple_product(const int keys[][2], const int values[], int n, DictItem *sorted_items) {
    for (int i = 0; i < n; i++) {
        sorted_items[i].key[0] = keys[i][0];
        sorted_items[i].key[1] = keys[i][1];
        sorted_items[i].value = values[i];
        sorted_items[i].product = tuple_product(keys[i], 2);
    }
    qsort(sorted_items, n, sizeof(DictItem), compare_dict_items);
}

int main() {
    int keys[][2] = {{2, 3}, {1, 5}, {4, 2}, {3, 3}, {2, 2}};
    int values[] = {10, 20, 30, 40, 50};
    int n = sizeof(keys) / sizeof(keys[0]);
    
    DictItem *sorted_items = (DictItem *)malloc(n * sizeof(DictItem));
    if (sorted_items == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    sort_dictionary_by_tuple_product(keys, values, n, sorted_items);
    
    printf("Sorted dictionary items by tuple product:\n");
    for (int i = 0; i < n; i++) {
        printf("Key: (%d, %d), Value: %d, Product: %lld\n", 
               sorted_items[i].key[0], sorted_items[i].key[1], 
               sorted_items[i].value, sorted_items[i].product);
    }
    
    free(sorted_items);
    return 0;
}