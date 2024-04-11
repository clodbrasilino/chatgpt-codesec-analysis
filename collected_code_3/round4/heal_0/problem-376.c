#include <stdio.h>

#define MAX 100
#define CUSTOM_VALUE -1

void removeDuplicates(int arr[], int n) {
    int i, j, k;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n;) {
            if (arr[j] == arr[i]) {
                for (k = j; k < n; k++) {
                    arr[k] = arr[k + 1];
                }
                n--;
            } else {
                j++;
            }
        }
    }

    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}

int main() {
    int n, i, arr[MAX];

    printf("Enter number of elements in the array : ");
    scanf("%d", &n);

    printf("Enter elements in array : ");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nArray before removing duplicates : ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\nArray after removing duplicates : ");
    removeDuplicates(arr, n);

    return 0;
}