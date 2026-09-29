#include <stdio.h>
#include <stdlib.h>

void heapify(int *arr, int n, int i) {
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
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        int temp = arr[i];
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[smallest]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        arr[i] = arr[smallest];
        arr[smallest] = temp;
        heapify(arr, n, smallest);
    }
}

void buildHeap(int *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}

void findSmallestIntegers(int *arr, int n, int k) {
    buildHeap(arr, n);

    for (int i = 0; i < k; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        int smallest = arr[0];
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[n-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        arr[0] = arr[n - 1];
        arr[n - 1] = smallest;
        n--;
        heapify(arr, n, 0);
    }
}

int main() {
    int arr[] = {4, 7, 2, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
  
    findSmallestIntegers(arr, n, k);
  
    printf("Smallest %d integers: ", k);
    for (int i = 0; i < k; i++)
        printf("%d ", arr[n - k + i]);

    return 0;
}