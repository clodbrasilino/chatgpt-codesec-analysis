#include <stdio.h>
#include <stdlib.h>

int sum_column(int** list_of_lists, int num_lists, int num_list_items, int column) {
    if (column >= num_list_items || column < 0) {
        printf("Error: Column index out of range.\n");
        exit(1);
    }

    int sum = 0;
    for (int i = 0; i < num_lists; i++) {
        if (list_of_lists[i] == NULL) {
            printf("Error: Encountered null pointer.\n");
            exit(1);
        }
        sum += list_of_lists[i][column];
    }

    return sum;
}

int main() {
    int num_lists = 3;
    int num_list_items = 3;

    int** list_of_lists = malloc(num_lists * sizeof(int*));
    if(list_of_lists == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }

    for(int i = 0; i < num_lists; i++) {
        list_of_lists[i] = malloc(num_list_items * sizeof(int));
        if(list_of_lists[i] == NULL) {
            printf("Error: Memory allocation failed.\n");
            exit(1);
        }
        for(int j = 0; j < num_list_items; j++) {
            list_of_lists[i][j] = i + j;
        }
    }

    int column_to_sum = 1;
    int sum = sum_column(list_of_lists, num_lists, num_list_items, column_to_sum);
    printf("Sum of column %d is %d\n", column_to_sum, sum);

    for(int i = 0; i < num_lists; i++) {
        free(list_of_lists[i]);
    }
    free(list_of_lists);

    return 0;
}