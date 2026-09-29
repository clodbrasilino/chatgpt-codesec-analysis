#include <stdio.h>

typedef struct {
    int x;
    int y;
} Tuple;

int sum_tuple_elements(Tuple* tuple_arr, int len) {
    int sum = 0;

    if(tuple_arr != NULL) {
        for(int i = 0; i < len; i++) {
            sum += tuple_arr[i].x + tuple_arr[i].y;
        }
    }

    return sum;
}

int main() {
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8},
        {9, 10},
    };

    int sum = sum_tuple_elements(tuples, sizeof(tuples) / sizeof(tuples[0]));

    printf("The sum of tuple elements is: %d\n", sum);

    return 0;
}