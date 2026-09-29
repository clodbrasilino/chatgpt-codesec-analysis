#include <stdio.h>

#define MAX_SIZE 100

void removeDuplicates(int arr[], int *size) {
    int i, j, k;

    for(i = 0; i < *size; i++) {
        for(j = i+1; j < *size; j++) {
            if(arr[i] == arr[j]) {
                for(k = j; k < *size; k++) {
                    arr[k] = arr[k + 1];
                }
                (*size)--;
                j--;
            }
        }
    }
}

int main() {
    int arr[MAX_SIZE], size, i;

    printf("Enter size of the array : ");
    scanf("%d", &size);

    printf("Enter elements in array : ");
    for(i=0; i<size; i++) {
        scanf("%d", &arr[i]);
    }

    removeDuplicates(arr, &size);

    printf("\nArray after removing duplicates : ");
    for(i=0; i<size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}