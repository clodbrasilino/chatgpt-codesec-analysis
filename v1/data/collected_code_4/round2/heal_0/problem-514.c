#include <stdio.h>

int sum_tuple_elements(int tuple[], int size) {
    int sum = 0;
    for(int i = 0; i < size; ++i) {
        sum += tuple[i];
    }
    return sum;
}

void sum_tuple_list_elements(int **tuple_list, int *tuple_sizes, int list_size) {
    for(int i = 0; i < list_size; ++i) {
        printf("Sum of tuple %d: %d\n", i, sum_tuple_elements(tuple_list[i], tuple_sizes[i]));
    }
}

int main() {
    int tuple_1[] = {1, 2, 3, 4, 5};
    int tuple_2[] = {6, 7, 8, 9, 10};
    int tuple_3[] = {11, 12, 13, 14, 15};

    int *tuple_list[] = {tuple_1, tuple_2, tuple_3};
    int tuple_sizes[] = {5, 5, 5};
    int list_size = 3;

    sum_tuple_list_elements(tuple_list, tuple_sizes, list_size);

    return 0;
}