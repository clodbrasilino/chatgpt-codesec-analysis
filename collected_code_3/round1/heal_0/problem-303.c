#include <stdio.h>

int getInversionCount(int arr[], int n) {
    int inv_count = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j])
                inv_count++;
    return inv_count;
}

int areInversionsSame(int arr1[], int arr2[], int n) {
    int inv_count1 = getInversionCount(arr1, n);
    int inv_count2 = getInversionCount(arr2, n);
    return inv_count1 == inv_count2;
}

int main() {
    int arr1[] = {1, 20, 6, 4, 5};
    int arr2[] = {2, 4, 1, 3, 5};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    if (areInversionsSame(arr1, arr2, n))
        printf("Inversions are same.\n");
    else
        printf("Inversions are not same.\n");
    return 0;
}