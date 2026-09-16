#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int value;
    int arrIdx;
    int elemIdx;
} HeapNode;

static int cmpInt(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

static void heapSwap(HeapNode *a, HeapNode *b)
{
    HeapNode tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heapifyDown(HeapNode *heap, int size, int i)
{
    while (1) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < size && heap[left].value < heap[smallest].value) {
            smallest = left;
        }
        if (right < size && heap[right].value < heap[smallest].value) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }
        heapSwap(&heap[i], &heap[smallest]);
        i = smallest;
    }
}

int findSmallestRange(int *const *arrays, const int *sizes, int k,
                      int *rangeStart, int *rangeEnd)
{
    HeapNode *heap;
    int currentMax;
    long long bestRange;
    int i;

    if (arrays == NULL || sizes == NULL || k <= 0 ||
        rangeStart == NULL || rangeEnd == NULL) {
        return -1;
    }

    heap = malloc((size_t)k * sizeof *heap);
    if (heap == NULL) {
        return -1;
    }

    currentMax = INT_MIN;
    for (i = 0; i < k; i++) {
        if (arrays[i] == NULL || sizes[i] <= 0) {
            free(heap);
            return -1;
        }
        heap[i].value = arrays[i][0];
        heap[i].arrIdx = i;
        heap[i].elemIdx = 0;
        if (heap[i].value > currentMax) {
            currentMax = heap[i].value;
        }
    }

    for (i = k / 2 - 1; i >= 0; i--) {
        heapifyDown(heap, k, i);
    }

    bestRange = LLONG_MAX;
    while (1) {
        HeapNode minNode = heap[0];
        long long range = (long long)currentMax - (long long)minNode.value;
        if (range < bestRange) {
            bestRange = range;
            *rangeStart = minNode.value;
            *rangeEnd = currentMax;
        }
        if (minNode.elemIdx + 1 >= sizes[minNode.arrIdx]) {
            break;
        }
        heap[0].value = arrays[minNode.arrIdx][minNode.elemIdx + 1];
        heap[0].elemIdx = minNode.elemIdx + 1;
        if (heap[0].value > currentMax) {
            currentMax = heap[0].value;
        }
        heapifyDown(heap, k, 0);
    }

    free(heap);
    return 0;
}

int main(void)
{
    int a1[] = {4, 10, 15, 24, 26};
    int a2[] = {0, 9, 12, 20};
    int a3[] = {5, 18, 22, 30};
    int *arrays[3];
    int sizes[3];
    int rangeStart;
    int rangeEnd;
    int status;

    arrays[0] = a1;
    arrays[1] = a2;
    arrays[2] = a3;
    sizes[0] = (int)(sizeof a1 / sizeof a1[0]);
    sizes[1] = (int)(sizeof a2 / sizeof a2[0]);
    sizes[2] = (int)(sizeof a3 / sizeof a3[0]);

    qsort(a1, (size_t)sizes[0], sizeof a1[0], cmpInt);
    qsort(a2, (size_t)sizes[1], sizeof a2[0], cmpInt);
    qsort(a3, (size_t)sizes[2], sizeof a3[0], cmpInt);

    status = findSmallestRange(arrays, sizes, 3, &rangeStart, &rangeEnd);
    if (status != 0) {
        fprintf(stderr, "Failed to compute smallest range\n");
        return EXIT_FAILURE;
    }

    printf("Smallest range: [%d, %d]\n", rangeStart, rangeEnd);
    return EXIT_SUCCESS;
}