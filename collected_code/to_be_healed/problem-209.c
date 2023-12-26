#include <stdio.h>

// Function to swap two integers
void swap(int *a, int *b) {
    /* Possible weaknesses found:
     *  Cannot determine that '*a' is initialized [premium-bughuntingUninit]
     */
    int temp = *a;
    /* Possible weaknesses found:
     *  Cannot determine that '*b' is initialized [premium-bughuntingUninit]
     */
    *a = *b;
    *b = temp;
}

// Function to perform min-heapify
void heapify(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    /* Possible weaknesses found:
     *  Cannot determine that 'arr[left]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'arr[smallest]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    /* Possible weaknesses found:
     *  Cannot determine that 'arr[right]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'arr[smallest]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        heapify(arr, n, smallest);
    }
}

// Function to delete the smallest element from the heap and insert a new item
void deleteAndInsert(int arr[], int n, int item) {
    if (n <= 0)
        return;

    arr[0] = item;
    heapify(arr, n, 0);
}

// Function to print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        printf("%d ", arr[i]);
    printf("\n");
}

// Program entry point
int main() {
    int arr[] = {4, 10, 3, 5, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    deleteAndInsert(arr, n, 2);

    printf("Array after deletion and insertion: ");
    printArray(arr, n);
    
    return 0;
}