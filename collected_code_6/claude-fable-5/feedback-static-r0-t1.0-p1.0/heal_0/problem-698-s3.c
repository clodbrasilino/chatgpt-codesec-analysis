#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key_first;
    int key_second;
    int value;
} DictItem;

static long long tuple_product(const DictItem *item)
{
    return (long long)item->key_first * (long long)item->key_second;
}

static int compare_items(const void *a, const void *b)
{
    const DictItem *item_a = (const DictItem *)a;
    const DictItem *item_b = (const DictItem *)b;
    long long prod_a = tuple_product(item_a);
    long long prod_b = tuple_product(item_b);

    if (prod_a < prod_b) {
        return -1;
    }
    if (prod_a > prod_b) {
        return 1;
    }
    return 0;
}

static int sort_dict_by_tuple_product(DictItem *items, size_t count)
{
    if (items == NULL || count == 0U) {
        return -1;
    }
    qsort(items, count, sizeof(DictItem), compare_items);
    return 0;
}

static void print_items(const DictItem *items, size_t count)
{
    size_t i;

    if (items == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        if (printf("(%d, %d): %d\n", items[i].key_first,
                   items[i].key_second, items[i].value) < 0) {
            return;
        }
    }
}

int main(void)
{
    size_t count = 4U;
    DictItem *items = malloc(count * sizeof(DictItem));

    if (items == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    items[0].key_first = 5;
    items[0].key_second = 6;
    items[0].value = 3;

    items[1].key_first = 2;
    items[1].key_second = 3;
    items[1].value = 9;

    items[2].key_first = 8;
    items[2].key_second = 4;
    items[2].value = 10;

    items[3].key_first = 6;
    items[3].key_second = 4;
    items[3].value = 12;

    if (printf("Before sorting:\n") < 0) {
        free(items);
        return EXIT_FAILURE;
    }
    print_items(items, count);

    if (sort_dict_by_tuple_product(items, count) != 0) {
        fprintf(stderr, "Sorting failed\n");
        free(items);
        return EXIT_FAILURE;
    }

    if (printf("After sorting by tuple product:\n") < 0) {
        free(items);
        return EXIT_FAILURE;
    }
    print_items(items, count);

    free(items);
    return EXIT_SUCCESS;
}