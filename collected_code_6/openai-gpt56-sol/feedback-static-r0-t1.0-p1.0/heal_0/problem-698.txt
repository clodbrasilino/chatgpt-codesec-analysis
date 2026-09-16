#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct {
    int64_t first;
    int64_t second;
} TupleKey;

typedef struct {
    TupleKey key;
    const char *value;
} DictionaryItem;

static int compare_items(const void *lhs, const void *rhs)
{
    const DictionaryItem *a = lhs;
    const DictionaryItem *b = rhs;
    int64_t a_product;
    int64_t b_product;

    if (__builtin_mul_overflow(a->key.first, a->key.second, &a_product) ||
        __builtin_mul_overflow(b->key.first, b->key.second, &b_product)) {
        if (a->key.first != b->key.first) {
            return (a->key.first > b->key.first) - (a->key.first < b->key.first);
        }
        return (a->key.second > b->key.second) -
               (a->key.second < b->key.second);
    }

    if (a_product != b_product) {
        return (a_product > b_product) - (a_product < b_product);
    }
    if (a->key.first != b->key.first) {
        return (a->key.first > b->key.first) - (a->key.first < b->key.first);
    }
    return (a->key.second > b->key.second) -
           (a->key.second < b->key.second);
}

static int sort_dictionary_by_tuple_product(DictionaryItem *items, size_t count)
{
    if (items == NULL && count != 0U) {
        return -1;
    }

    qsort(items, count, sizeof(*items), compare_items);
    return 0;
}

int main(void)
{
    DictionaryItem dictionary[] = {
        {{2, 3}, "alpha"},
        {{-4, 2}, "beta"},
        {{5, 1}, "gamma"},
        {{3, 3}, "delta"},
        {{-2, -2}, "epsilon"}
    };
    const size_t count = sizeof(dictionary) / sizeof(dictionary[0]);

    if (sort_dictionary_by_tuple_product(dictionary, count) != 0) {
        fputs("Failed to sort dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t product;

        if (__builtin_mul_overflow(dictionary[i].key.first,
                                   dictionary[i].key.second,
                                   &product)) {
            fputs("Tuple product overflow.\n", stderr);
            return EXIT_FAILURE;
        }

        if (printf("(%" PRId64 ", %" PRId64 "): %s [product=%" PRId64 "]\n",
                   dictionary[i].key.first,
                   dictionary[i].key.second,
                   dictionary[i].value,
                   product) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}