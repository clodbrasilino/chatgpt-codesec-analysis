#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t len;
} Tuple;

typedef struct {
    int *a;
    int *b;
    size_t len;
} ZippedTuple;

ZippedTuple zip_tuples(const Tuple *t1, const Tuple *t2) {
    ZippedTuple result = {NULL, NULL, 0};
    if (t1 == NULL || t2 == NULL) {
        return result;
    }

    size_t min_len = t1->len < t2->len ? t1->len : t2->len;
    if (min_len == 0) {
        return result;
    }

    result.a = (int *)malloc(min_len * sizeof(int));
    result.b = (int *)malloc(min_len * sizeof(int));

    if (result.a == NULL || result.b == NULL) {
        free(result.a);
        free(result.b);
        result.a = NULL;
        result.b = NULL;
        result.len = 0;
        return result;
    }

    for (size_t i = 0; i < min_len; ++i) {
        result.a[i] = t1->items[i];
        result.b[i] = t2->items[i];
    }

    result.len = min_len;
    return result;
}

void free_zipped(ZippedTuple *zt) {
    if (zt != NULL) {
        free(zt->a);
        free(zt->b);
        zt->a = NULL;
        zt->b = NULL;
        zt->len = 0;
    }
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 7, 8};

    Tuple t1 = {arr1, 5};
    Tuple t2 = {arr2, 3};

    ZippedTuple zt = zip_tuples(&t1, &t2);

    if (zt.a != NULL && zt.b != NULL) {
        for (size_t i = 0; i < zt.len; ++i) {
            printf("(%d, %d)\n", zt.a[i], zt.b[i]);
        }
    }

    free_zipped(&zt);

    return 0;
}