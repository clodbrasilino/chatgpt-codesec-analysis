#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    int size;
} Tuple;

int max_nth_column(Tuple *list, int tuple_count, int n) {
    if (list == NULL || tuple_count <= 0) {
        return 0;
    }
    if (n < 0 || n >= list[0].size) {
        return 0;
    }
    
    int max = list[0].values[n];
    for (int i = 1; i < tuple_count; i++) {
        if (list[i].values[n] > max) {
            max = list[i].values[n];
        }
    }
    return max;
}

int main(void) {
    int values1[] = {10, 20, 30};
    int values2[] = {40, 50, 60};
    int values3[] = {70, 80, 90};
    
    Tuple list[3];
    list[0].values = values1;
    list[0].size = 3;
    list[1].values = values2;
    list[1].size = 3;
    list[2].values = values3;
    list[2].size = 3;
    
    int result = max_nth_column(list, 3, 1);
    printf("Maximum of column 1: %d\n", result);
    
    result = max_nth_column(list, 3, 0);
    printf("Maximum of column 0: %d\n", result);
    
    result = max_nth_column(list, 3, 2);
    printf("Maximum of column 2: %d\n", result);
    
    return 0;
}