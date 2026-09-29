#include <stdio.h>
#include <stdlib.h>

int count_pairs_with_sum(int *arr, int n, int sum) {
    if (arr == NULL || n < 0) {
        return 0;
    }

    int count = 0;
    int *visited = (int *)calloc(n, sizeof(int));
    if (visited == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == sum && !visited[i] && !visited[j]) {
                count++;
                visited[i] = 1;
                visited[j] = 1;
                break;
            }
        }
    }

    free(visited);
    return count;
}

int main(void) {
    int arr[] = {1, 5, 7, -1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 6;

    int result = count_pairs_with_sum(arr, n, sum);

    printf("%d\n", result);

    return 0;
}