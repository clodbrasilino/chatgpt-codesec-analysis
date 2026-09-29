#include <stdio.h>
#include <stdlib.h>

void print_combination(int *arr, int *data, int start, int end, int index, int r)
{
    if (index == r) {
        for (int i = 0; i < r; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
        return;
    }
    
    for (int i = start; i <= end && end - i + 1 >= r - index; i++) {
        data[index] = arr[i];
        print_combination(arr, data, i + 1, end, index + 1, r);
    }
}

void find_combinations(int *arr, int n, int r)
{
    if (arr == NULL || n <= 0 || r <= 0 || r > n) {
        return;
    }
    
    int *data = malloc(r * sizeof(int));
    if (data == NULL) {
        return;
    }
    
    print_combination(arr, data, 0, n - 1, 0, r);
    
    free(data);
}

int main(void)
{
    int arr[] = {1, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    for (int r = 1; r <= n; r++) {
        printf("Combinations of size %d:\n", r);
        find_combinations(arr, n, r);
    }
    
    return 0;
}