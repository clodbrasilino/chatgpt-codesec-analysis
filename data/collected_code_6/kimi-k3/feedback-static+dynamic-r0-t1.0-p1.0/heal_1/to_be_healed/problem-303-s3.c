#include <stdio.h>
#include <stdlib.h>

long long merge_and_count(int arr[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    long long inv_count = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1);
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return inv_count;
}

long long merge_sort_and_count(int arr[], int temp[], int left, int right) {
    long long inv_count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        inv_count += merge_sort_and_count(arr, temp, left, mid);
        inv_count += merge_sort_and_count(arr, temp, mid + 1, right);
        inv_count += merge_and_count(arr, temp, left, mid, right);
    }
    return inv_count;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
long long count_inversions(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }
    
    int *temp = (int *)malloc(n * sizeof(int));
    if (temp == NULL) {
        return -1;
    }
    
    int *arr_copy = (int *)malloc(n * sizeof(int));
    if (arr_copy == NULL) {
        free(temp);
        return -1;
    }
    
    for (int i = 0; i < n; i++) {
        arr_copy[i] = arr[i];
    }
    
    long long result = merge_sort_and_count(arr_copy, temp, 0, n - 1);
    
    free(temp);
    free(arr_copy);
    
    return result;
}

int check_inversion_count(int arr1[], int n1, int arr2[], int n2) {
    if (arr1 == NULL || arr2 == NULL || n1 <= 0 || n2 <= 0) {
        return -1;
    }
    
    long long inv1 = count_inversions(arr1, n1);
    long long inv2 = count_inversions(arr2, n2);
    
    if (inv1 == -1 || inv2 == -1) {
        return -1;
    }
    
    return (inv1 == inv2) ? 1 : 0;
}

int main() {
    int arr1[] = {1, 20, 6, 4, 5};
    int arr2[] = {8, 4, 2, 1, 3};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    int result = check_inversion_count(arr1, n1, arr2, n2);
    
    if (result == 1) {
        printf("Both arrays have the same inversion count.\n");
    } else if (result == 0) {
        printf("Arrays have different inversion counts.\n");
    } else {
        printf("Error in processing arrays.\n");
    }
    
    return 0;
}