#include <stdio.h>
#define MAX_SIZE 100

void printDuplicates(int arr[], int size) {
    int i, j;
    for(i = 0; i < size; i++) {
        for(j = i + 1; j < size; j++) {
            if(arr[i] == arr[j]) {
                printf("%d ", arr[i]);
                break;
            }
        }
    }
}

int main() {
    int arr[MAX_SIZE];
    int i, size;

    printf("Enter size of the array : ");
    scanf("%d", &size);

    printf("Enter elements in array : ");
    for(i=0; i<size; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Duplicate elements are: ");
    printDuplicates(arr, size);

    return 0;
}