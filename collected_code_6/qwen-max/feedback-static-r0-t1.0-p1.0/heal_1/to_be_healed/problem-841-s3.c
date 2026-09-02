#include <stdio.h>
#include <stdlib.h>

int mergeCount(int *arr, int tempArr[], int left, int mid, int right) {
    int i, j, k;
    int inv_count = 0;

    i = left;
    j = mid;
    k = left;

    while ((i <= mid - 1) && (j <= right)) {
        if (arr[i] <= arr[j]) {
            tempArr[k++] = arr[i++];
        } else {
            tempArr[k++] = arr[j++];

            inv_count = inv_count + (mid - i);
        }
    }

    while (i <= mid - 1)
        tempArr[k++] = arr[i++];

    while (j <= right)
        tempArr[k++] = arr[j++];

    for (i = left; i <= right; i++)
        arr[i] = tempArr[i];

    return inv_count;
}

int mergeSortCount(int *arr, int tempArr[], int left, int right) {
    /* Possible weaknesses found:
     *  The scope of the variable 'mid' can be reduced. [variableScope]
     */
    int mid, inv_count = 0;
    if (right > left) {
        mid = (right + left) / 2;

        inv_count  = mergeSortCount(arr, tempArr, left, mid);
        inv_count += mergeSortCount(arr, tempArr, mid + 1, right);

        inv_count += mergeCount(arr, tempArr, left, mid + 1, right);
    }
    return inv_count;
}

int countInversions(int *arr, int n) {
    int *tempArr = (int*)malloc(n * sizeof(int));
    if (!tempArr) return -1; // Error in allocation

    int result = mergeSortCount(arr, tempArr, 0, n - 1);

    free(tempArr);
    return result;
}

int main() {
    int arr[] = {1, 20, 6, 4, 5};
    int n = 5;
    printf("Number of inversions are %d\n", countInversions(arr, n));
    return 0;
}