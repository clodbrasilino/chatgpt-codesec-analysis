#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    int first;
    int second;
} Pair;

typedef struct {
    Pair *pairs;
    size_t size;
} ZippedResult;

ZippedResult zip_tuples(const Tuple *tuple1, const Tuple *tuple2) {
    ZippedResult result;
    result.pairs = NULL;
    result.size = 0;

    if (!tuple1 || !tuple2 || !tuple1->elements || !tuple2->elements) {
        return result;
    }

    size_t min_size = tuple1->size < tuple2->size ? tuple1->size : tuple2->size;

    result.pairs = (Pair *)malloc(min_size * sizeof(Pair));
    if (!result.pairs) {
        return result;
    }

    result.size = min_size;

    for (size_t i = 0; i < min_size; ++i) {
        result.pairs[i].first = tuple1->elements[i];
        result.pairs[i].second = tuple2->elements[i];
    }

    return result;
}

int main(void) {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6, 7};

    Tuple t1 = {arr1, sizeof(arr1) / sizeof(arr1[0])};
    Tuple t2 = {arr2, sizeof(arr2) / sizeof(arr2[0])};

    ZippedResult zipped = zip_tuples(&t1, &t2);

    if (zipped.pairs) {
        for (size_t i = 0; i < zipped.size; ++i) {
            printf("(%d, %d)\n", zipped.pairs[i].first, zipped.pairs[i].second);
        }
        free(zipped.pairs);
    }

    return 0;
}