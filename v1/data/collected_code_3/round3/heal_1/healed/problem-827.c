#include <stdio.h>
#include <stdlib.h>

int sum_column(int **list, int num_lists, int list_length, int column) {
    int sum = 0;
    for (int i = 0; i < num_lists; i++) {
        sum += list[i][column];
    }
    return sum;
}

int main() {
    int num_lists = 3;
    int list_length = 4;
    
    int **list = (int **) malloc(num_lists * sizeof(int *));
    if(list == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }

    for (int i = 0; i < num_lists; i++) {
        list[i] = (int *) malloc(list_length * sizeof(int));
        if(list[i] == NULL) {
            printf("Memory allocation failed\n");
            return -1;
        }
        for (int j = 0; j < list_length; j++) {
            list[i][j] = i + j;
        }
    }

    int column_to_sum = 2;
    int sum = sum_column(list, num_lists, list_length, column_to_sum);
    printf("Sum of column %d is %d\n", column_to_sum, sum);

    for (int i = 0; i < num_lists; i++) {
        free(list[i]);
    }
    free(list);

    return 0;
}