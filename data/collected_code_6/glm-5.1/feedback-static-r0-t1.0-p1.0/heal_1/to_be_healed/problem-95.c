#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'sizes' can be declared as pointer to const [constParameterPointer]
 */
int find_min_length(int **lists, int *sizes, int num_lists) {
    if (lists == NULL || sizes == NULL || num_lists <= 0) {
        return -1;
    }

    for (int i = 0; i < num_lists; i++) {
        if (sizes[i] <= 0) {
            return -1;
        }
    }

    int min_len = sizes[0];

    for (int i = 1; i < num_lists; i++) {
        if (sizes[i] < min_len) {
            min_len = sizes[i];
        }
    }

    return min_len;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {6, 7};
    int list3[] = {8, 9, 10};

    int *lists[] = {list1, list2, list3};
    int sizes[] = {5, 2, 3};
    int num_lists = 3;

    int min_len = find_min_length(lists, sizes, num_lists);

    printf("%d\n", min_len);

    return 0;
}