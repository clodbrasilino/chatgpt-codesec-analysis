#include <stdio.h>
#include <stdlib.h>

long long mergeAndCount(int arr[], int temp[], int left, int mid, int right, int type) {
    int i = left;
    int j = mid;
    int k = left;
    long long invCount = 0;

    while (i <= mid - 1 && j <= right) {
        if (type == 0) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
                invCount += (mid - i);
            }
        } else {
            if (arr[i] >= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
                invCount += (mid - i);
            }
        }
    }

    while (i <= mid - 1) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return invCount;
}

long long mergeSortAndCount(int arr[], int temp[], int left, int right, int type) {
    long long invCount = 0;
    if (right > left) {
        int mid = (right + left) / 2;

        invCount += mergeSortAndCount(arr, temp, left, mid, type);
        invCount += mergeSortAndCount(arr, temp, mid + 1, right, type);
        invCount += mergeAndCount(arr, temp, left, mid + 1, right, type);
    }
    return invCount;
}

long long countInversions(const int arr[], int n, int type) {
    int *temp = (int *)malloc(n * sizeof(int));
    if (temp == NULL) {
        return -1;
    }
    int *arrCopy = (int *)malloc(n * sizeof(int));
    if (arrCopy == NULL) {
        free(temp);
        return -1;
    }
    for (int i = 0; i < n; i++) {
        arrCopy[i] = arr[i];
    }
    long long result = mergeSortAndCount(arrCopy, temp, 0, n - 1, type);
    free(temp);
    free(arrCopy);
    return result;
}

int areInversionCountsSame(const int arr[], int n) {
    long long type1 = countInversions(arr, n, 0);
    if (type1 == -1) {
        return -1;
    }
    long long type2 = countInversions(arr, n, 1);
    if (type2 == -1) {
        return -1;
    }
    return (type1 == type2) ? 1 : 0;
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input.\n");
            free(arr);
            return 1;
        }
    }

    int result = areInversionCountsSame(arr, n);
    if (result == -1) {
        printf("Memory allocation failed.\n");
    } else if (result == 1) {
        printf("The inversion counts are the same.\n");
    } else {
        printf("The inversion counts are not the same.\n");
    }

    free(arr);
    return 0;
}