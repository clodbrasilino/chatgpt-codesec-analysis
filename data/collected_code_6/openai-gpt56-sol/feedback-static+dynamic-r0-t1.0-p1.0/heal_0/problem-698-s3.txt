#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

typedef struct {
    int64_t first;
    int64_t second;
} TupleKey;

typedef struct {
    TupleKey key;
    const char *value;
} DictionaryItem;

static int compare_tuple_products(const void *lhs, const void *rhs)
{
    const DictionaryItem *a = lhs;
    const DictionaryItem *b = rhs;
    __int128 product_a = (__int128)a->key.first * a->key.second;
    __int128 product_b = (__int128)b->key.first * b->key.second;

    if (product_a < product_b) {
        return -1;
    }
    if (product_a > product_b) {
        return 1;
    }
    if (a->key.first < b->key.first) {
        return -1;
    }
    if (a->key.first > b->key.first) {
        return 1;
    }
    if (a->key.second < b->key.second) {
        return -1;
    }
    if (a->key.second > b->key.second) {
        return 1;
    }
    return 0;
}

static int sort_dictionary_items(DictionaryItem *items, size_t count)
{
    if (items == NULL && count != 0U) {
        return -1;
    }
    if (count > SIZE_MAX / sizeof(*items)) {
        return -1;
    }

    qsort(items, count, sizeof(*items), compare_tuple_products);
    return 0;
}

int main(void)
{
    DictionaryItem dictionary[] = {
        {{2, 3}, "alpha"},
        {{-4, 2}, "beta"},
        {{5, 1}, "gamma"},
        {{-3, -3}, "delta"},
        {{0, 7}, "epsilon"}
    };
    const size_t count = sizeof(dictionary) / sizeof(dictionary[0]);

    if (sort_dictionary_items(dictionary, count) != 0) {
        fputs("Failed to sort dictionary items.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < count; ++index) {
        if (printf("(%" PRId64 ", %" PRId64 "): %s\n",
                   dictionary[index].key.first,
                   dictionary[index].key.second,
                   dictionary[index].value) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}