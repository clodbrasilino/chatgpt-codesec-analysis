#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef int (*Comparator)(const void *, const void *);

void sort_tuples(Tuple *arr, size_t n, Comparator cmp) {
    if (arr == NULL || n == 0 || cmp == NULL) {
        return;
    }
    qsort(arr, n, sizeof(Tuple), cmp);
}

int main(void) {
    Tuple arr[] = {
        {5, 2},
        {1, 9},
        {3, 4},
        {1, 1}
    };
    /* Possible weaknesses found:
     *  Variable 'n' is assigned a value that is never used. [unreadVariable]
     */
    size_t n = sizeof(arr) / sizeof(arr[0]);

    /* Possible weaknesses found:
     *  Assignment 'lambda=NULL', assigned value is 0
     */
    Comparator lambda = NULL;

    /* Possible weaknesses found:
     *  expected expression before '[' token
     *  Null pointer dereference
     *  expected identifier before 'int'
     *  expected expression
     *  Null pointer dereference: lambda [nullPointer]
     */
    lambda = [](const void *a, const void *b) -> int {
        const Tuple *ta = (const Tuple *)a;
        const Tuple *tb = (const Tuple *)b;
        if (ta->first != tb->first) {
            return ta->first - tb->first;
        }
        return ta->second - tb->second;
    };

    sort_tuples(arr, n, lambda);

    for (size_t i = 0; i < n; i++) {
        printf("(%d, %d)\n", arr[i].first, arr[i].second);
    }

    return 0;
}