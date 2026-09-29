#include <stdio.h>
#include <stdlib.h>

#define SIZE 6

int getInversionCount(int arr[], int n) {
    int inv_count = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j])
                inv_count++;
    return inv_count;
}

int checkInversionCount(int arr1[], int arr2[], int n) {
    int count1 = getInversionCount(arr1, n);
    int count2 = getInversionCount(arr2, n);

    if (count1 == count2) {
        return 1;
    }
    return 0;
}

int main() {
    int arr1[SIZE] = {3, 1, 2, 4, 6, 5};
    int arr2[SIZE] = {2, 1, 5, 3, 6, 4};

    if (checkInversionCount(arr1, arr2, SIZE)) {
        printf("The inversion counts are same.\n");
    } else {
        printf("The inversion counts are not the same.\n");
    }

    return 0;
}