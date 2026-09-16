#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    long long val;
    int prime_idx;
    int ugly_idx;
} HeapNode;

static void swapNodes(HeapNode *a, HeapNode *b) {
    HeapNode tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heapPush(HeapNode *heap, int *size, HeapNode node) {
    int i = (*size)++;
    heap[i] = node;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent].val <= heap[i].val) {
            break;
        }
        swapNodes(&heap[parent], &heap[i]);
        i = parent;
    }
}

static HeapNode heapPop(HeapNode *heap, int *size) {
    HeapNode top = heap[0];
    (*size)--;
    heap[0] = heap[*size];
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < *size && heap[left].val < heap[smallest].val) {
            smallest = left;
        }
        if (right < *size && heap[right].val < heap[smallest].val) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }
        swapNodes(&heap[i], &heap[smallest]);
        i = smallest;
    }
    return top;
}

int nthSuperUglyNumber(int n, int *primes, int primesSize) {
    if (n <= 0 || primes == NULL || primesSize <= 0) {
        return -1;
    }
    for (int i = 0; i < primesSize; ++i) {
        if (primes[i] <= 1) {
            return -1;
        }
    }
    if (n == 1) {
        return 1;
    }

    long long *ugly = malloc((size_t)n * sizeof(long long));
    HeapNode *heap = malloc((size_t)primesSize * sizeof(HeapNode));
    if (ugly == NULL || heap == NULL) {
        free(ugly);
        free(heap);
        return -1;
    }

    ugly[0] = 1LL;
    int heapSize = 0;
    for (int i = 0; i < primesSize; ++i) {
        HeapNode node;
        node.val = (long long)primes[i];
        node.prime_idx = i;
        node.ugly_idx = 0;
        heapPush(heap, &heapSize, node);
    }

    for (int i = 1; i < n; ++i) {
        long long next = heap[0].val;
        ugly[i] = next;
        while (heapSize > 0 && heap[0].val == next) {
            HeapNode node = heapPop(heap, &heapSize);
            node.ugly_idx++;
            node.val = (long long)primes[node.prime_idx] * ugly[node.ugly_idx];
            heapPush(heap, &heapSize, node);
        }
    }

    long long result = ugly[n - 1];
    free(ugly);
    free(heap);

    if (result > INT_MAX || result < 0) {
        return -1;
    }
    return (int)result;
}

int main(void) {
    int primes[] = { 2, 7, 13, 19 };
    int n = 12;
    int result = nthSuperUglyNumber(n, primes, (int)(sizeof(primes) / sizeof(primes[0])));
    printf("%d\n", result);
    return 0;
}