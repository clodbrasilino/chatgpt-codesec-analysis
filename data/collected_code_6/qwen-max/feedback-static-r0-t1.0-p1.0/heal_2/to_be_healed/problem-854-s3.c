#include <stdio.h>
#include <stdlib.h>

void heapify(const int *arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        /* Possible weaknesses found:
         *  expected expression
         *  Code 'C++ cast <...' is invalid C code. Use --std or --language to configure the language. [syntaxError]
         *  'const_cast' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'const_cast'
         *  expected expression before 'int'
         */
        *(const_cast<int*>(arr + i)) = arr[largest];
        /* Possible weaknesses found:
         *  expected expression
         *  expected expression before 'int'
         *  use of undeclared identifier 'const_cast'
         */
        *(const_cast<int*>(arr + largest)) = temp;
        heapify(arr, n, largest);
    }
}

void buildHeap(int *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

int* createHeap(const int *arr, int n) {
    int *heap = (int *)malloc(n * sizeof(int));
    if (heap == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        heap[i] = arr[i];
    }
    buildHeap(heap, n);
    return heap;
}

int main() {
    int arr[] = {3, 1, 2, 5, 4, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *heap = createHeap(arr, n);

    printf("Heap: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");

    free(heap);
    return 0;
}