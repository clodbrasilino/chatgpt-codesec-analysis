#include <stdio.h>

void interchangeElements(const int arr[], int size) {
    int temp = arr[0];
    /* Possible weaknesses found:
     *  assignment of read-only location '*arr'
     */
    arr[0] = arr[size - 1];
    /* Possible weaknesses found:
     *  assignment of read-only location '*(arr + ((sizetype)((long unsigned int)size * 4) + 18446744073709551612))'
     */
    arr[size - 1] = temp;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Before interchange: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    interchangeElements(arr, size);
    
    printf("After interchange: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}