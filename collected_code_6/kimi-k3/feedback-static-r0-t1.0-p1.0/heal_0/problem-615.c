#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleOfTuples;

double find_average(const TupleOfTuples *tt) {
    if (tt == NULL || tt->tuples == NULL || tt->count == 0) {
        return 0.0;
    }

    double sum = 0.0;
    size_t total_elements = 0;

    for (size_t i = 0; i < tt->count; i++) {
        if (tt->tuples[i].data == NULL || tt->tuples[i].size == 0) {
            continue;
        }
        for (size_t j = 0; j < tt->tuples[i].size; j++) {
            sum += tt->tuples[i].data[j];
            total_elements++;
        }
    }

    if (total_elements == 0) {
        return 0.0;
    }

    return sum / total_elements;
}

int main(void) {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5};
    int data3[] = {6, 7, 8, 9};

    Tuple t1 = {data1, 3};
    Tuple t2 = {data2, 2};
    Tuple t3 = {data3, 4};

    Tuple tuples_array[] = {t1, t2, t3};
    TupleOfTuples tt = {tuples_array, 3};

    double avg = find_average(&tt);
    printf("Average: %.2f\n", avg);

    return 0;
}