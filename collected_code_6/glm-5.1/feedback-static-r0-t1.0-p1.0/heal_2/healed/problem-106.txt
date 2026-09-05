#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int count;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

TupleList add_list_to_tuples(TupleList list, int const *addends, int addend_count) {
    if (list.tuples == NULL || list.count == 0) {
        return list;
    }

    if (addends == NULL || addend_count == 0) {
        return list;
    }

    for (int i = 0; i < list.count; i++) {
        Tuple *current = &list.tuples[i];
        if (current->elements == NULL || current->count == 0) {
            continue;
        }

        int min_count = current->count < addend_count ? current->count : addend_count;
        for (int j = 0; j < min_count; j++) {
            current->elements[j] += addends[j];
        }
    }

    return list;
}

int main(void) {
    int *data1 = malloc(3 * sizeof(int));
    data1[0] = 1; data1[1] = 2; data1[2] = 3;
    
    int *data2 = malloc(2 * sizeof(int));
    data2[0] = 4; data2[1] = 5;
    
    const int addends[] = {10, 20};

    Tuple t1 = {data1, 3};
    Tuple t2 = {data2, 2};
    Tuple *tuples_array = malloc(2 * sizeof(Tuple));
    tuples_array[0] = t1;
    tuples_array[1] = t2;
    
    TupleList list = {tuples_array, 2};

    TupleList result = add_list_to_tuples(list, addends, 2);

    for (int i = 0; i < result.count; i++) {
        for (int j = 0; j < result.tuples[i].count; j++) {
            printf("%d ", result.tuples[i].elements[j]);
        }
        printf("\n");
    }

    free(data1);
    free(data2);
    free(tuples_array);

    return 0;
}