#include <stdio.h>
#include <stdlib.h>

void print_combination(int *arr, int n, int *data, int start, int index, int r) {
    if (index == r) {
        for (int j = 0; j < r; j++) {
            printf("%d ", data[j]);
        }
        printf("\n");
        return;
    }

    for (int i = start; i <= n && n - i + 1 >= r - index; i++) {
        data[index] = arr[i];
        print_combination(arr, n, data, i + 1, index + 1, r);
    }
}

void find_combinations(int *arr, int size, int r) {
    int *data = (int *)malloc(r * sizeof(int));
    if (data == NULL) {
        exit(EXIT_FAILURE);
    }
    print_combination(arr, size - 1, data, 0, 0, r);
    free(data);
}

int main() {
    int arr[] = {1, 2, 3, 4};
    int r = 2;
    int n = sizeof(arr) / sizeof(arr[0]);

    find_combinations(arr, n, r);

    return 0;
}