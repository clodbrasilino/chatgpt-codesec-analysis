#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; did you forget to '#include <limits.h>'?
  */

typedef struct {
    int value;
    int idx;
    int input_idx;
} Node;

void heapify(Node* heap, int n, int i) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && heap[l].value < heap[smallest].value)
        smallest = l;

    if (r < n && heap[r].value < heap[smallest].value)
        smallest = r;

    if (smallest != i) {
        Node temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        
        heapify(heap, n, smallest);
    }
}

void mergeSortedInputs(int *inputs[], int numInputs, int numElements) {
    Node* heap = (Node*) malloc(numInputs * sizeof(Node));
    
    for (int i = 0; i < numInputs; i++) {
        heap[i].value = inputs[i][0];
        heap[i].idx = 0;
        heap[i].input_idx = i;
    }

    for (int i = numInputs / 2 - 1; i >= 0; i--)
        heapify(heap, numInputs, i);
    
    for (int i = 0; i < numElements; i++) {
        printf("%d ", heap[0].value);

        int input_idx = heap[0].input_idx;
        int idx = heap[0].idx + 1;

        if (idx < numElements) {
            heap[0].value = inputs[input_idx][idx];
            heap[0].idx = idx;
        }
        else {
            /* Possible weaknesses found:
             *  each undeclared identifier is reported only once for each function it appears in
             *  'INT_MAX' undeclared (first use in this function)
             */
            heap[0].value = INT_MAX;
        }

        heapify(heap, numInputs, 0);
    }

    free(heap);
}

int main() {
    int input1[] = {1, 3, 5};
    int input2[] = {2, 4, 6};
    int* inputs[] = {input1, input2};
    
    int numInputs = sizeof(inputs)/sizeof(inputs[0]);
    int numElements = sizeof(input1)/sizeof(input1[0]);
    
    mergeSortedInputs(inputs, numInputs, numElements);
    
    return 0;
}