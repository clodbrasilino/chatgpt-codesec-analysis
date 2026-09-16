#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int value;
    size_t listIndex;
} MergeNode;

typedef struct {
    int value;
    int freq;
} FreqEntry;

static void swapMergeNodes(MergeNode *a, MergeNode *b)
{
    MergeNode temp = *a;
    *a = *b;
    *b = temp;
}

static void mergeHeapPush(MergeNode *heap, size_t *size, MergeNode node)
{
    size_t i = *size;
    heap[i] = node;
    (*size)++;
    while (i > 0) {
        size_t parent = (i - 1) / 2;
        if (heap[parent].value <= heap[i].value) {
            break;
        }
        swapMergeNodes(&heap[parent], &heap[i]);
        i = parent;
    }
}

static MergeNode mergeHeapPop(MergeNode *heap, size_t *size)
{
    MergeNode top = heap[0];
    size_t i = 0;
    (*size)--;
    heap[0] = heap[*size];
    for (;;) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t smallest = i;
        if (left < *size && heap[left].value < heap[smallest].value) {
            smallest = left;
        }
        if (right < *size && heap[right].value < heap[smallest].value) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }
        swapMergeNodes(&heap[i], &heap[smallest]);
        i = smallest;
    }
    return top;
}

static int freqEntryLess(FreqEntry a, FreqEntry b)
{
    if (a.freq != b.freq) {
        return a.freq < b.freq;
    }
    return a.value < b.value;
}

static void swapFreqEntries(FreqEntry *a, FreqEntry *b)
{
    FreqEntry temp = *a;
    *a = *b;
    *b = temp;
}

static void freqHeapPush(FreqEntry *heap, size_t *size, FreqEntry entry)
{
    size_t i = *size;
    heap[i] = entry;
    (*size)++;
    while (i > 0) {
        size_t parent = (i - 1) / 2;
        if (!freqEntryLess(heap[i], heap[parent])) {
            break;
        }
        swapFreqEntries(&heap[parent], &heap[i]);
        i = parent;
    }
}

static FreqEntry freqHeapPop(FreqEntry *heap, size_t *size)
{
    FreqEntry top = heap[0];
    size_t i = 0;
    (*size)--;
    heap[0] = heap[*size];
    for (;;) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t smallest = i;
        if (left < *size && freqEntryLess(heap[left], heap[smallest])) {
            smallest = left;
        }
        if (right < *size && freqEntryLess(heap[right], heap[smallest])) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }
        swapFreqEntries(&heap[i], &heap[smallest]);
        i = smallest;
    }
    return top;
}

static void topKConsider(FreqEntry *heap, size_t *size, size_t k, FreqEntry entry)
{
    if (*size < k) {
        freqHeapPush(heap, size, entry);
    } else if (freqEntryLess(heap[0], entry)) {
        freqHeapPop(heap, size);
        freqHeapPush(heap, size, entry);
    }
}

int *topKFrequent(const int *const *lists, const size_t *listSizes,
                  size_t numLists, size_t k, size_t *resultSize)
{
    MergeNode *mergeHeap = NULL;
    FreqEntry *freqHeap = NULL;
    size_t *positions = NULL;
    int *result = NULL;
    size_t totalElements = 0;
    size_t heapSize = 0;
    size_t freqSize = 0;
    size_t count;
    size_t i;
    int haveCurrent = 0;
    int currentValue = 0;
    int currentFreq = 0;

    if (resultSize == NULL) {
        return NULL;
    }
    *resultSize = 0;
    if (lists == NULL || listSizes == NULL || numLists == 0 || k == 0) {
        return NULL;
    }
    if (numLists > SIZE_MAX / sizeof(MergeNode) ||
        numLists > SIZE_MAX / sizeof(size_t)) {
        return NULL;
    }
    for (i = 0; i < numLists; i++) {
        if (listSizes[i] > 0 && lists[i] == NULL) {
            return NULL;
        }
        if (listSizes[i] > SIZE_MAX - totalElements) {
            return NULL;
        }
        totalElements += listSizes[i];
    }
    if (totalElements == 0) {
        return NULL;
    }
    if (k > totalElements) {
        k = totalElements;
    }

    mergeHeap = malloc(numLists * sizeof(*mergeHeap));
    freqHeap = malloc(k * sizeof(*freqHeap));
    positions = calloc(numLists, sizeof(*positions));
    if (mergeHeap == NULL || freqHeap == NULL || positions == NULL) {
        free(mergeHeap);
        free(freqHeap);
        free(positions);
        return NULL;
    }

    for (i = 0; i < numLists; i++) {
        if (listSizes[i] > 0) {
            MergeNode node;
            node.value = lists[i][0];
            node.listIndex = i;
            positions[i] = 1;
            mergeHeapPush(mergeHeap, &heapSize, node);
        }
    }

    while (heapSize > 0) {
        MergeNode node = mergeHeapPop(mergeHeap, &heapSize);
        if (haveCurrent && node.value == currentValue) {
            currentFreq++;
        } else {
            if (haveCurrent) {
                FreqEntry entry;
                entry.value = currentValue;
                entry.freq = currentFreq;
                topKConsider(freqHeap, &freqSize, k, entry);
            }
            currentValue = node.value;
            currentFreq = 1;
            haveCurrent = 1;
        }
        if (positions[node.listIndex] < listSizes[node.listIndex]) {
            MergeNode next;
            next.value = lists[node.listIndex][positions[node.listIndex]];
            next.listIndex = node.listIndex;
            positions[node.listIndex]++;
            mergeHeapPush(mergeHeap, &heapSize, next);
        }
    }
    if (haveCurrent) {
        FreqEntry entry;
        entry.value = currentValue;
        entry.freq = currentFreq;
        topKConsider(freqHeap, &freqSize, k, entry);
    }

    count = freqSize;
    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        free(mergeHeap);
        free(freqHeap);
        free(positions);
        return NULL;
    }
    for (i = count; i > 0; i--) {
        FreqEntry entry = freqHeapPop(freqHeap, &freqSize);
        result[i - 1] = entry.value;
    }

    free(mergeHeap);
    free(freqHeap);
    free(positions);
    *resultSize = count;
    return result;
}

int main(void)
{
    int list1[] = {1, 4, 5, 7, 9};
    int list2[] = {1, 2, 4, 5, 8};
    int list3[] = {1, 3, 4, 5, 6};
    const int *lists[] = {list1, list2, list3};
    /* Possible weaknesses found:
     *  Variable 'listSizes' can be declared as const array [constVariable]
     */
    size_t listSizes[] = {5, 5, 5};
    size_t numLists = 3;
    size_t k = 3;
    size_t resultSize = 0;
    size_t i;
    int *result;

    result = topKFrequent(lists, listSizes, numLists, k, &resultSize);
    if (result == NULL) {
        fprintf(stderr, "Failed to compute top %zu frequent integers.\n", k);
        return EXIT_FAILURE;
    }

    printf("Top %zu most frequent integers:\n", resultSize);
    for (i = 0; i < resultSize; i++) {
        printf("%d\n", result[i]);
    }

    free(result);
    return EXIT_SUCCESS;
}