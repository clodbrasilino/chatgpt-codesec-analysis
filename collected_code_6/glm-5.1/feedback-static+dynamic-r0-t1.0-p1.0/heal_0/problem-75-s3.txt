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

TupleList find_divisible_tuples(TupleList list, int k) {
    TupleList result;
    result.tuples = malloc(list.count * sizeof(Tuple));
    if (result.tuples == NULL) {
        result.count = 0;
        return result;
    }
    result.count = 0;

    if (k == 0) {
        return result;
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

    return result;
}

int main() {
    int data0[] = {2, 4, 6};
    int data1[] = {3, 5, 7};
    int data2[] = {10, 20, 0};
    int data3[] = {9, 18, 27};
    
    Tuple t0 = {data0, 3};
    Tuple t1 = {data1, 3};
    Tuple t2 = {data2, 3};
    Tuple t3 = {data3, 3};
    
    Tuple input_tuples[] = {t0, t1, t2, t3};
    TupleList input_list = {input_tuples, 4};
    
    int k = 2;
    TupleList output_list = find_divisible_tuples(input_list, k);
    
    for (int i = 0; i < output_list.count; i++) {
        printf("(");
        for (int j = 0; j < output_list.tuples[i].size; j++) {
            printf("%d", output_list.tuples[i].elements[j]);
            if (j < output_list.tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }
    
    free(output_list.tuples);
    
    return 0;
}