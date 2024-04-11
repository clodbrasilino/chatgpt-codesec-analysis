#include <stdio.h>

#define MAX_LISTS 10
#define MAX_ELEMENTS 10

int* find_highest_sum_list(int lists[MAX_LISTS][MAX_ELEMENTS], int list_size[MAX_LISTS], int num_lists) {
    int max_sum = -1;
    int *max_list = NULL;

    for(int i = 0; i < num_lists; i++) {
        int current_sum = 0;
        for(int j = 0; j < list_size[i]; j++) {
            current_sum += lists[i][j];
        }
        if(current_sum > max_sum) {
            max_sum = current_sum;
            max_list = lists[i];
        }
    }

    return max_list;
}

int main() {
    int lists[MAX_LISTS][MAX_ELEMENTS] = {
        {1, 2, 3, 4, 5},
        {2, 3, 4, 5, 6},
        {3, 4, 5, 6, 7},
        {4, 5, 6, 7, 8},
        {5, 6, 7, 8, 9}
    };
    int list_size[MAX_LISTS] = {5, 5, 5, 5, 5};
    int num_lists = 5;
    int *max_list = find_highest_sum_list(lists, list_size, num_lists); 

    int max_list_index = 0;
    for (int i = 0; i < num_lists; i++) {
        if(lists[i] == max_list) {
           max_list_index = i;
           break;
        }
    }

    printf("List with highest sum is: ");
    for(int i = 0; i < list_size[max_list_index]; i++) {
        printf("%d ", max_list[i]);
    }

    return 0;
}