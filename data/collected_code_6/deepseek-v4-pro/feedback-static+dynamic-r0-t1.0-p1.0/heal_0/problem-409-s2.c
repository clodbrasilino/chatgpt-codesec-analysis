#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *data;
    size_t size;
} List;

long long min_product_from_pairs(const List *list) {
    if (list == NULL || list->data == NULL || list->size < 2) {
        return LLONG_MAX;
    }

    long long min_product = LLONG_MAX;
    int found = 0;

    for (size_t i = 0; i < list->size; i++) {
        for (size_t j = i + 1; j < list->size; j++) {
            long long product;
            if (__builtin_mul_overflow((long long)(list->data[i].first * list->data[j].first),
                                       (long long)(list->data[i].second * list->data[j].second),
                                       &product)) {
                continue;
            }

            if (!found || product < min_product) {
                min_product = product;
                found = 1;
            }
        }
    }

    return found ? min_product : LLONG_MAX;
}

int main(void) {
    Tuple tuples[] = {
        {2, 3},
        {-1, 4},
        {5, -2},
        {1, 7},
        {-3, -6}
    };
    List list = {tuples, sizeof(tuples) / sizeof(tuples[0])};

    long long result = min_product_from_pairs(&list);

    if (result == LLONG_MAX) {
        printf("No valid pairs found\n");
    } else {
        printf("Minimum product from pairs: %lld\n", result);
    }

    Tuple empty_tuples[] = {};
    List empty_list = {empty_tuples, 0};
    result = min_product_from_pairs(&empty_list);
    if (result == LLONG_MAX) {
        printf("Empty list: No valid pairs found\n");
    }

    return 0;
}