#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int inner_size;
    int *inner;
} Tuple;

typedef struct {
    int outer_size;
    Tuple *tuples;
} TupleOfTuples;

double average_of_tuple_of_tuples(const TupleOfTuples *tt) {
    if (tt == NULL || tt->tuples == NULL || tt->outer_size <= 0) {
        return 0.0;
    }

    long long sum = 0;
    long long count = 0;

    for (int i = 0; i < tt->outer_size; i++) {
        if (tt->tuples[i].inner != NULL && tt->tuples[i].inner_size > 0) {
            for (int j = 0; j < tt->tuples[i].inner_size; j++) {
                sum += tt->tuples[i].inner[j];
                count++;
            }
        }
    }

    if (count == 0) {
        return 0.0;
    }

    return (double)sum / (double)count;
}

int main(void) {
    int inner1[] = {1, 2, 3};
    int inner2[] = {4, 5};
    int inner3[] = {6, 7, 8, 9};

    Tuple tuples[3] = {
        {3, inner1},
        {2, inner2},
        {4, inner3}
    };

    TupleOfTuples tt = {3, tuples};

    double avg = average_of_tuple_of_tuples(&tt);
    printf("Average: %.2f\n", avg);

    TupleOfTuples empty_tt = {0, NULL};
    printf("Empty average: %.2f\n", average_of_tuple_of_tuples(&empty_tt));

    TupleOfTuples null_tt = {2, NULL};
    printf("Null tuples average: %.2f\n", average_of_tuple_of_tuples(&null_tt));

    Tuple tuples_with_null[2];
    tuples_with_null[0].inner = inner1;
    tuples_with_null[0].inner_size = 3;
    tuples_with_null[1].inner = NULL;
    tuples_with_null[1].inner_size = 0;

    TupleOfTuples tt_with_null = {2, tuples_with_null};
    printf("With null inner average: %.2f\n", average_of_tuple_of_tuples(&tt_with_null));

    return 0;
}