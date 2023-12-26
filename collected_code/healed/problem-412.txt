#include <stdio.h>

void removeOddNumbers(const int* arr, const int size) {
    int temp[size];
    int j = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            temp[j] = arr[i];
            j++;
        }
    }

    printf("List without odd numbers: ");
    for (int i = 0; i < j; i++) {
        printf("%d ", temp[i]);
    }
    printf("\n");
}

int main() {
    const int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const int size = sizeof(arr) / sizeof(arr[0]);

    removeOddNumbers(arr, size);

    return 0;
}