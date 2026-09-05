#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

int all_divisible(Tuple t, int k) {
    if (k == 0) {
        return 0;
    }
    for (int i = 0; i < t.size; i++) {
        if (t.elements[i] % k != 0) {
            return 0;
        }
    }
    return 1;
}

TupleList find_divisible_tuples(TupleList list, int k) {
    TupleList result;
    result.tuples = malloc(list.count * sizeof(Tuple));
    if (result.tuples == NULL) {
        result.count = 0;
        return result;
    }
    result.count = 0;

    for (int i = 0; i < list.count; i++) {
        if (all_divisible(list.tuples[i], k)) {
            result.tuples[result.count] = list.tuples[i];
            result.count++;
        }
    }

    Tuple *temp = realloc(result.tuples, result.count * sizeof(Tuple));
    if (temp != NULL || result.count == 0) {
        result.tuples = temp;
    }

    return result;
}

int main() {
    int data0[] = {2, 4, 6};
    int data1[] = {3, 5, 7};
    int data2[] = {8, 10, 12};
    int data3[] = {1, 2, 3};

    Tuple t0 = {data0, 3};
    Tuple t1 = {data1, 3};
    Tuple t2 = {data2, 3};
    Tuple t3 = {data3, 3};

    Tuple original_tuples[] = {t0, t1, t2, t3};
    TupleList list = {original_tuples, 4};

    int k = 2;
    TupleList result = find_divisible_tuples(list, k);

    for (int i = 0; i < result.count; i++) {
        printf("(");
        for (int j = 0; j < result.tuples[i].size; j++) {
            printf("%d", result.tuples[i].elements[j]);
            if (j < result.tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    free(result.tuples);

    return 0;
}