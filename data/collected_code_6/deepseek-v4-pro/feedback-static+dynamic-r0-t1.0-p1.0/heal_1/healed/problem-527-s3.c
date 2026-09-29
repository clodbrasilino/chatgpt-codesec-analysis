#include <stdio.h>
#include <stdlib.h>

void find_pairs(const int *arr, int size, int target) {
    if (arr == NULL || size <= 0) {
        return;
    }

    int *visited = (int *)calloc(size, sizeof(int));
    if (visited == NULL) {
        return;
    }

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (!visited[i] && !visited[j] && arr[i] + arr[j] == target) {
                printf("(%d, %d)\n", arr[i], arr[j]);
                visited[i] = 1;
                visited[j] = 1;
            }
        }
    }

    free(visited);
}

int main(void) {
    int arr[] = {1, 5, 7, -1, 5, 3, 3, 4, 2};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 6;

    find_pairs(arr, size, target);

    return 0;
}