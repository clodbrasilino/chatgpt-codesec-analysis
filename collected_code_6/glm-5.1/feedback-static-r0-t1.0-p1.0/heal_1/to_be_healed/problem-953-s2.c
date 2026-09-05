#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_min_subsets(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int *sorted = (int *)malloc(n * sizeof(int));
    if (sorted == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }

    qsort(sorted, n, sizeof(int), cmp);

    int max_freq = 1;
    int current_freq = 1;

    for (int i = 1; i < n; i++) {
        if (sorted[i] == sorted[i - 1]) {
            current_freq++;
            if (current_freq > max_freq) {
                max_freq = current_freq;
            }
        } else {
            current_freq = 1;
        }
    }

    free(sorted);
    sorted = NULL;

    return max_freq;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", find_min_subsets(arr1, n1));

    int arr2[] = {1, 1, 2, 2, 3, 3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", find_min_subsets(arr2, n2));

    int arr3[] = {5, 5, 5, 5, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", find_min_subsets(arr3, n3));

    printf("%d\n", find_min_subsets(NULL, 0));

    return 0;
}