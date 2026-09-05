#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} List;

List find_max_sum_list(List *lists, int num_lists) {
    if (lists == NULL || num_lists <= 0) {
        List empty = {NULL, 0};
        return empty;
    }

    int max_index = 0;
    long long max_sum = 0;

    for (int i = 0; i < lists[0].size; i++) {
        max_sum += lists[0].elements[i];
    }

    for (int i = 1; i < num_lists; i++) {
        long long current_sum = 0;
        if (lists[i].elements != NULL) {
            for (int j = 0; j < lists[i].size; j++) {
                current_sum += lists[i].elements[j];
            }
        }
        if (current_sum > max_sum) {
            max_sum = current_sum;
            max_index = i;
        }
    }

    return lists[max_index];
}

int main() {
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6, 7};
    int c[] = {-1, -2};

    List lists[3];
    lists[0].elements = a;
    lists[0].size = 3;
    lists[1].elements = b;
    lists[1].size = 4;
    lists[2].elements = c;
    lists[2].size = 2;

    List result = find_max_sum_list(lists, 3);

    printf("List with highest sum has size %d and elements: ", result.size);
    for (int i = 0; i < result.size; i++) {
        printf("%d ", result.elements[i]);
    }
    printf("\n");

    return 0;
}