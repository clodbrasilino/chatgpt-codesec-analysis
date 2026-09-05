#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_last_removed_position(int *arr, int size, int *positions, int num_removals) {
    if (arr == NULL || positions == NULL || num_removals <= 0) {
        return -1;
    }
    int total_missing = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == -1) {
            if (total_missing < num_removals) {
                positions[total_missing] = i;
                total_missing++;
            }
        }
    }
    if (total_missing == 0) {
        return -1;
    }
    return total_missing;
}

int main(void) {
    int arr[] = {10, -1, 30, -1, 50, -1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int *positions = (int *)malloc(size * sizeof(int));
    if (positions == NULL) {
        return 1;
    }
    int num_removals = find_last_removed_position(arr, size, positions, size);
    if (num_removals > 0) {
        printf("%d\n", positions[num_removals - 1]);
    }
    free(positions);
    return 0;
}