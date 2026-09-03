#include <stdio.h>
#include <stdlib.h>

int count_lists(int num_lists, int **lists) {
    if (num_lists <= 0 || lists == NULL) {
        return 0;
    }
    for (int i = 0; i < num_lists; ++i) {
        if (lists[i] == NULL) {
            return 0;
        }
    }
    return num_lists;
}

int main() {
    int num_lists = 5;
    int *list1 = (int *)malloc(3 * sizeof(int));
    int *list2 = (int *)malloc(4 * sizeof(int));
    int *list3 = (int *)malloc(2 * sizeof(int));
    int *list4 = (int *)malloc(1 * sizeof(int));
    int *list5 = (int *)malloc(5 * sizeof(int));

    int *lists[] = {list1, list2, list3, list4, list5};

    int result = count_lists(num_lists, lists);

    printf("Number of lists: %d\n", result);

    free(list1);
    free(list2);
    free(list3);
    free(list4);
    free(list5);

    return 0;
}