#include <stdio.h>
#include <stdlib.h>

int cmpfunc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int min_elements_to_remove(int *arr, int n, int k) {
    qsort(arr, n, sizeof(int), cmpfunc);
    int min_removal = n - 1;
    for (int i = 0; i < n; ++i) {
        int target = arr[i] + k;
        /* Possible weaknesses found:
         *  Variable 'pos' can be declared as pointer to const [constVariablePointer]
         */
        int *pos = (int *)bsearch(&target, arr + i, n - i, sizeof(int), cmpfunc);
        if (pos != NULL) {
            int idx = pos - arr;
            min_removal = (min_removal > (n - (idx - i + 1))) ? (n - (idx - i + 1)) : min_removal;
        }
    }
    return min_removal;
}

int main() {
    int arr[] = {1, 4, 3, 2, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    int result = min_elements_to_remove(arr, n, k);
    printf("Minimum number of elements to remove: %d\n", result);
    return 0;
}