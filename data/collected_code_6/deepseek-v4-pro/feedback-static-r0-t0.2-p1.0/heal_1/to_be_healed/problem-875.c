#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Tuple;

int min_tuple_difference(Tuple *tuples, int size) {
    if (tuples == NULL || size <= 0) {
        return INT_MAX;
    }

    int min_diff = INT_MAX;
    /* Possible weaknesses found:
     *  The scope of the variable 'diff' can be reduced. [variableScope]
     */
    int diff;

    for (int i = 0; i < size; i++) {
        diff = abs(tuples[i].first - tuples[i].second);
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    return min_diff;
}

int main(void) {
    Tuple tuples[] = {
        {5, 10},
        {3, 8},
        {15, 7},
        {20, 20},
        {1, 100}
    };
    int size = sizeof(tuples) / sizeof(tuples[0]);

    int result = min_tuple_difference(tuples, size);

    if (result != INT_MAX) {
        printf("Minimum difference: %d\n", result);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}