#include <stdio.h>
#include <stdlib.h>

void find_frequency(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return;
    }

    int *visited = (int *)malloc(size * sizeof(int));
    if (visited == NULL) {
        return;
    }

    for (int i = 0; i < size; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        if (visited[i] == 1) {
            continue;
        }

        int count = 1;
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                count++;
                visited[j] = 1;
            }
        }

        printf("%d occurs %d times\n", arr[i], count);
    }

    free(visited);
}

int main() {
    int arr[] = {1, 2, 3, 2, 4, 1, 5, 1};
    int size = sizeof(arr) / sizeof(arr[0]);

    find_frequency(arr, size);

    return 0;
}