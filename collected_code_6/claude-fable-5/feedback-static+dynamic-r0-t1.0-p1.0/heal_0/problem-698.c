#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key_first;
    int key_second;
    int value;
} DictItem;

static int compare_by_product(const void *a, const void *b)
{
    const DictItem *item_a = (const DictItem *)a;
    const DictItem *item_b = (const DictItem *)b;
    long long product_a = (long long)item_a->key_first * (long long)item_a->key_second;
    long long product_b = (long long)item_b->key_first * (long long)item_b->key_second;

    if (product_a < product_b) {
        return -1;
    }
    if (product_a > product_b) {
        return 1;
    }
    return 0;
}

static int sort_dict_by_key_product(DictItem *items, size_t count)
{
    if (items == NULL || count == 0U) {
        return -1;
    }
    qsort(items, count, sizeof(DictItem), compare_by_product);
    return 0;
}

static void print_dict(const DictItem *items, size_t count)
{
    size_t i;

    if (items == NULL) {
        return;
    }
    printf("{");
    for (i = 0U; i < count; i++) {
        printf("(%d, %d): %d", items[i].key_first, items[i].key_second, items[i].value);
        if (i + 1U < count) {
            printf(", ");
        }
    }
    printf("}\n");
}

int main(void)
{
    DictItem dict[] = {
        {5, 6, 3},
        {2, 3, 9},
        {8, 4, 10},
        {6, 4, 12},
        {1, 2, 7}
    };
    size_t count = sizeof(dict) / sizeof(dict[0]);

    printf("Original dictionary:\n");
    print_dict(dict, count);

    if (sort_dict_by_key_product(dict, count) != 0) {
        fprintf(stderr, "Error: failed to sort dictionary\n");
        return EXIT_FAILURE;
    }

    printf("Sorted by key tuple product:\n");
    print_dict(dict, count);

    return EXIT_SUCCESS;
}