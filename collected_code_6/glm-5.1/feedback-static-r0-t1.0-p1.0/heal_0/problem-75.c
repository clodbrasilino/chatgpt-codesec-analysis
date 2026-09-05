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

TupleList find_tuples_divisible_by_k(TupleList list, int k) {
    TupleList result;
    result.tuples = NULL;
    result.count = 0;

    if (k == 0) {
        return result;
    }

    result.tuples = (Tuple *)malloc(list.count * sizeof(Tuple));
    if (result.tuples == NULL) {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < list.count; i++) {
        int divisible = 1;
        for (int j = 0; j < list.tuples[i].size; j++) {
            if (list.tuples[i].elements[j] % k != 0) {
                divisible = 0;
                break;
            }
        }
        if (divisible) {
            result.tuples[result.count] = list.tuples[i];
            result.count++;
        }
    }

    Tuple *temp = (Tuple *)realloc(result.tuples, result.count * sizeof(Tuple));
    if (temp != NULL || result.count == 0) {
        result.tuples = temp;
    }

    return result;
}

int main() {
    int data1[] = {2, 4, 6};
    int data2[] = {3, 5, 7};
    int data3[] = {8, 10, 12};
    int data4[] = {1, 2};

    Tuple tuples[] = {
        {data1, 3},
        {data2, 3},
        {data3, 3},
        {data4, 2}
    };

    TupleList list = {tuples, 4};
    int k = 2;

    TupleList result = find_tuples_divisible_by_k(list, k);

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