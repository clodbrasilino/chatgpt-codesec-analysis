#include <stdio.h>
#include <stdlib.h>

int count_lists(int num_lists) {
    int *lists = malloc(num_lists * sizeof(int));
    if (lists == NULL) {
        return -1;
    }
    free(lists);
    return num_lists;
}

int main() {
    int num_lists = 5;
    int result = count_lists(num_lists);
    if (result != -1) {
        printf("Number of lists: %d\n", result);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}