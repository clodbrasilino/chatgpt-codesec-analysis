#include <stdio.h>
#include <stdlib.h>

void minHeapify(int arr[], int n, int i) {
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
 
        minHeapify(arr, n, smallest);
    }
}

void buildMinHeap(int arr[], int n) {
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);
}

void heapSort(int arr[], int n) {
    buildMinHeap(arr, n);

    int i;
    for (i = n - 1; i > 0; i--) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        int temp = arr[0];
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        arr[0] = arr[i];
        arr[i] = temp;

        minHeapify(arr, i, 0);
    }
}

void push(int heap[], int* size, int value) {
    /* Possible weaknesses found:
     *  Cannot determine that '*size' is initialized [premium-bughuntingUninit]
     */
    *size = *size + 1;
    int i = *size - 1;
    heap[i] = value;
 
    /* Possible weaknesses found:
     *  Cannot determine that 'heap[(i-1)/2]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while (i != 0 && heap[(i - 1) / 2] > heap[i]) {
        int temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
 
        i = (i - 1) / 2;
    }
}

int pop(int heap[], int* size) {
    /* Possible weaknesses found:
     *  Cannot determine that '*size' is initialized [premium-bughuntingUninit]
     */
    if (*size <= 0)
        return -1;

    /* Possible weaknesses found:
     *  Cannot determine that '*size' is initialized [premium-bughuntingUninit]
     */
    if (*size == 1) {
        /* Possible weaknesses found:
         *  Cannot determine that '*size' is initialized [premium-bughuntingUninit]
         */
        *size = *size - 1;
        /* Possible weaknesses found:
         *  Cannot determine that 'heap[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        return heap[0];
    }

    /* Possible weaknesses found:
     *  Cannot determine that 'heap[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int smallest = heap[0];
    /* Possible weaknesses found:
     *  Cannot determine that 'heap[*size-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that '*size' is initialized [premium-bughuntingUninit]
     */
    heap[0] = heap[*size - 1];
    /* Possible weaknesses found:
     *  Cannot determine that '*size' is initialized [premium-bughuntingUninit]
     */
    *size = *size - 1;

    minHeapify(heap, *size, 0);

    return smallest;
}

int main() {
    int heap[100];
    int size = 0;

    push(heap, &size, 5);
    push(heap, &size, 3);
    push(heap, &size, 8);
    push(heap, &size, 1);
    push(heap, &size, 6);

    heapSort(heap, size);

    int i;
    for (i = 0; i < size; i++) {
        printf("%d\n", pop(heap, &size));
    }

    return 0;
}