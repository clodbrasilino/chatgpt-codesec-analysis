#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    int size;
} Tuple;

int cumulative_sum(Tuple *list, int tuple_count) {
    int total = 0;
    for (int i = 0; i < tuple_count; i++) {
        for (int j = 0; j < list[i].size; j++) {
            total += list[i].values[j];
        }
    }
    return total;
}

int main(void) {
    int values1[] = {1, 2, 3};
    int values2[] = {4, 5};
    int values3[] = {6, 7, 8, 9};

    Tuple list[] = {
        {values1, 3},
        {values2, 2},
        {values3, 4}
    };

    int result = cumulative_sum(list, 3);
    printf("Cumulative sum: %d\n", result);

    return 0;
}