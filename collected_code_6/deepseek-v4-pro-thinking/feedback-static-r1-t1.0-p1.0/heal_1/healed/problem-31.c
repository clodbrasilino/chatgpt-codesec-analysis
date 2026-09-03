#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int value;
    int listIdx;
    int pos;
} MergeNode;

typedef struct {
    int value;
    int freq;
} FreqNode;

static int merge_less(const MergeNode *a, const MergeNode *b) {
    return a->value < b->value;
}

static int freq_less(const FreqNode *a, const FreqNode *b) {
    if (a->freq != b->freq) {
        return a->freq < b->freq;
    }
    return a->value < b->value;
}

static void merge_heap_push(MergeNode *heap, int *size, MergeNode node) {
    int i = (*size)++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (!merge_less(&node, &heap[parent])) {
            break;
        }
        heap[i] = heap[parent];
        i = parent;
    }
    heap[i] = node;
}

static MergeNode merge_heap_pop(MergeNode *heap, int *size) {
    MergeNode root = heap[0];
    int n = --(*size);
    if (n == 0) {
        return root;
    }
    MergeNode last = heap[n];
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < n && merge_less(&heap[left], &heap[smallest])) {
            smallest = left;
        }
        if (right < n && merge_less(&heap[right], &heap[smallest])) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }
        heap[i] = heap[smallest];
        i = smallest;
    }
    heap[i] = last;
    return root;
}

static void freq_heap_push(FreqNode *heap, int *size, FreqNode node) {
    int i = (*size)++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (!freq_less(&node, &heap[parent])) {
            break;
        }
        heap[i] = heap[parent];
        i = parent;
    }
    heap[i] = node;
}

static FreqNode freq_heap_pop(FreqNode *heap, int *size) {
    FreqNode root = heap[0];
    int n = --(*size);
    if (n == 0) {
        return root;
    }
    FreqNode last = heap[n];
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < n && freq_less(&heap[left], &heap[smallest])) {
            smallest = left;
        }
        if (right < n && freq_less(&heap[right], &heap[smallest])) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }
        heap[i] = heap[smallest];
        i = smallest;
    }
    heap[i] = last;
    return root;
}

static void topk_add(FreqNode *heap, int *size, int k, FreqNode node) {
    if (*size < k) {
        freq_heap_push(heap, size, node);
    } else if (freq_less(&heap[0], &node)) {
        freq_heap_pop(heap, size);
        freq_heap_push(heap, size, node);
    }
}

int *topKFrequent(int **lists, const int *listSizes, int numLists, int k, int *returnSize) {
    if (returnSize == NULL) {
        return NULL;
    }
    *returnSize = 0;

    if (numLists <= 0 || k <= 0 || lists == NULL || listSizes == NULL) {
        return NULL;
    }

    for (int i = 0; i < numLists; i++) {
        if (listSizes[i] < 0) {
            return NULL;
        }
        if (listSizes[i] > 0 && lists[i] == NULL) {
            return NULL;
        }
    }

    if ((size_t)numLists > SIZE_MAX / sizeof(MergeNode) ||
        (size_t)k > SIZE_MAX / sizeof(FreqNode)) {
        return NULL;
    }

    MergeNode *mergeHeap = malloc((size_t)numLists * sizeof(MergeNode));
    if (mergeHeap == NULL) {
        return NULL;
    }
    int mergeSize = 0;

    FreqNode *freqHeap = malloc((size_t)k * sizeof(FreqNode));
    if (freqHeap == NULL) {
        free(mergeHeap);
        return NULL;
    }
    int freqSize = 0;

    for (int i = 0; i < numLists; i++) {
        if (listSizes[i] > 0) {
            MergeNode node;
            node.value = lists[i][0];
            node.listIdx = i;
            node.pos = 0;
            merge_heap_push(mergeHeap, &mergeSize, node);
        }
    }

    while (mergeSize > 0) {
        MergeNode node = merge_heap_pop(mergeHeap, &mergeSize);
        int value = node.value;
        int freq = 1;

        if (node.pos + 1 < listSizes[node.listIdx]) {
            MergeNode next;
            next.value = lists[node.listIdx][node.pos + 1];
            next.listIdx = node.listIdx;
            next.pos = node.pos + 1;
            merge_heap_push(mergeHeap, &mergeSize, next);
        }

        while (mergeSize > 0 && mergeHeap[0].value == value) {
            MergeNode equalNode = merge_heap_pop(mergeHeap, &mergeSize);
            freq++;

            if (equalNode.pos + 1 < listSizes[equalNode.listIdx]) {
                MergeNode next;
                next.value = lists[equalNode.listIdx][equalNode.pos + 1];
                next.listIdx = equalNode.listIdx;
                next.pos = equalNode.pos + 1;
                merge_heap_push(mergeHeap, &mergeSize, next);
            }
        }

        FreqNode fn;
        fn.value = value;
        fn.freq = freq;
        topk_add(freqHeap, &freqSize, k, fn);
    }

    if (freqSize == 0) {
        free(mergeHeap);
        free(freqHeap);
        return NULL;
    }

    int *result = malloc((size_t)freqSize * sizeof(int));
    if (result == NULL) {
        free(mergeHeap);
        free(freqHeap);
        return NULL;
    }

    int resultSize = freqSize;
    for (int i = 0; i < resultSize; i++) {
        FreqNode fn = freq_heap_pop(freqHeap, &freqSize);
        result[resultSize - 1 - i] = fn.value;
    }

    *returnSize = resultSize;
    free(mergeHeap);
    free(freqHeap);
    return result;
}

int main(void) {
    int list1[] = {1, 2, 3, 4};
    int list2[] = {2, 3, 5};
    int list3[] = {3, 4, 5, 6};
    int *lists[] = {list1, list2, list3};
    const int listSizes[] = {4, 3, 4};
    int returnSize = 0;

    int *result = topKFrequent(lists, listSizes, 3, 2, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}