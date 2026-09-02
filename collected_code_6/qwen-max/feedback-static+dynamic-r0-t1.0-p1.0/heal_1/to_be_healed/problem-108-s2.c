#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

typedef struct {
    int value;
    int list_index;
    int element_index;
} HeapNode;

typedef int (*CompareFunc)(const void *, const void *);

void heapify(HeapNode *arr, int n, int i, CompareFunc cmp) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && cmp(&arr[left], &arr[largest]) < 0)
        largest = left;

    if (right < n && cmp(&arr[right], &arr[largest]) < 0)
        largest = right;

    if (largest != i) {
        HeapNode temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest, cmp);
    }
}

void build_min_heap(HeapNode *arr, int n, CompareFunc cmp) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, cmp);
}

int compare(const void *a, const void *b) {
    return ((HeapNode*)a)->value - ((HeapNode*)b)->value;
}

/* Possible weaknesses found:
 *  Parameter 'list_sizes' can be declared as pointer to const [constParameterPointer]
 */
int* getNext(HeapNode *heap, int *heap_size, int **lists, int *list_sizes, int num_lists, CompareFunc cmp) {
    if (*heap_size == 0) return NULL;

    HeapNode min_node = heap[0];
    heap[0] = heap[*heap_size - 1];
    (*heap_size)--;

    if (min_node.element_index + 1 < list_sizes[min_node.list_index]) {
        heap[0].value = lists[min_node.list_index][min_node.element_index + 1];
        heap[0].element_index = min_node.element_index + 1;
        heap[0].list_index = min_node.list_index;
        heapify(heap, *heap_size, 0, cmp);
    } else {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MAX'
         *  'INT_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         */
        heap[0].value = INT_MAX;
        heap[0].element_index = min_node.element_index + 1;
        heap[0].list_index = min_node.list_index;
        heapify(heap, *heap_size, 0, cmp);
    }

    /* Possible weaknesses found:
     *  Returning pointer to member variable 'value' that will be invalid when returning.
     *  Address of variable taken here.
     *  Returning pointer to member variable 'value' that will be invalid when returning. [returnDanglingLifetime]
     */
    return &min_node.value;
}

int main() {
    int lists[][5] = {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MAX'
         *  'INT_MAX' undeclared (first use in this function)
         *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
         */
        {1, 4, 7, 9, INT_MAX},
        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MAX'
         */
        {2, 6, 8, 10, INT_MAX},
        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MAX'
         */
        {3, 5, 11, 12, INT_MAX}
    };
    int list_sizes[] = {4, 4, 4};
    int num_lists = 3;

    HeapNode heap[num_lists];
    int heap_size = num_lists;

    for (int i = 0; i < num_lists; ++i) {
        heap[i].value = lists[i][0];
        heap[i].list_index = i;
        heap[i].element_index = 0;
    }

    build_min_heap(heap, heap_size, compare);

    int *result;
    while ((result = getNext(heap, &heap_size, (int**)lists, list_sizes, num_lists, compare)) != NULL) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MAX'
         */
        if (*result == INT_MAX) break;
        printf("%d ", *result);
    }

    return 0;
}