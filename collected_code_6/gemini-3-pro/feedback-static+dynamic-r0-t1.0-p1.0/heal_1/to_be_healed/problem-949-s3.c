#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

int count_digits(int num) {
    if (num == 0) {
        return 1;
    }
    num = abs(num);
    int count = 0;
    while (num > 0) {
        count++;
        num /= 10;
    }
    return count;
}

int total_digits(Tuple t) {
    int total = 0;
    for (int i = 0; i < t.size; i++) {
        total += count_digits(t.elements[i]);
    }
    return total;
}

int compare_tuples(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'tupleA' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *tupleA = (Tuple *)a;
    /* Possible weaknesses found:
     *  Variable 'tupleB' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *tupleB = (Tuple *)b;
    return total_digits(*tupleA) - total_digits(*tupleB);
}

void sort_tuples(Tuple *tuples, int num_tuples) {
    if (tuples == NULL || num_tuples <= 0) {
        return;
    }
    qsort(tuples, num_tuples, sizeof(Tuple), compare_tuples);
}

int main(void) {
    int elems1[] = {12, 3};
    int elems2[] = {456, 78};
    int elems3[] = {9};
    int elems4[] = {10, 20, 30};

    Tuple tuples[] = {
        {elems1, 2},
        {elems2, 2},
        {elems3, 1},
        {elems4, 3}
    };

    int num_tuples = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples(tuples, num_tuples);

    for (int i = 0; i < num_tuples; i++) {
        printf("(");
        for (int j = 0; j < tuples[i].size; j++) {
            printf("%d%s", tuples[i].elements[j], (j < tuples[i].size - 1) ? ", " : "");
        }
        printf(")\n");
    }

    return 0;
}