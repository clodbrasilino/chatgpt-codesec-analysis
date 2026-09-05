#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'size' can be declared as pointer to const [constParameterPointer]
 */
int heap_extract_min_and_insert(int *heap, int *size, int new_item) {
    if (heap == NULL || size == NULL || *size <= 0) {
        return -1;
    }

    int item = heap[0];
    heap[0] = new_item;
    int current = 0;
    int child = 2 * current + 1;

    while (child < *size) {
        if (child + 1 < *size && heap[child + 1] < heap[child]) {
            child++;
        }
        if (heap[current] <= heap[child]) {
            break;
        }
        int temp = heap[current];
        heap[current] = heap[child];
        heap[child] = temp;
        current = child;
        child = 2 * current + 1;
    }

    return item;
}

int main(void) {
    int size = 5;
    int *heap = (int *)malloc(size * sizeof(int));
    if (heap == NULL) {
        return 1;
    }

    heap[0] = 2;
    heap[1] = 5;
    heap[2] = 8;
    heap[3] = 10;
    heap[4] = 12;

    int min_val = heap_extract_min_and_insert(heap, &size, 3);
    printf("%d %d\n", min_val, heap[0]);

    free(heap);

    size = 0;
    int new_min_val = heap_extract_min_and_insert(heap, &size, 3);
    printf("%d\n", new_min_val);

    return 0;
}