#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long value;
    int prime;
    int index;
} HeapNode;

static void heapSwap(HeapNode *a, HeapNode *b) {
    HeapNode tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heapPush(HeapNode *heap, int *size, HeapNode node) {
    int i = *size;
    (*size)++;
    heap[i] = node;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent].value <= heap[i].value) {
            break;
        }
        heapSwap(&heap[parent], &heap[i]);
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
        if (left < *size && heap[left].value < heap[smallest].value) {
            smallest = left;
        }
        if (right < *size && heap[right].value < heap[smallest].value) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }
        heapSwap(&heap[i], &heap[smallest]);
        i = smallest;
    }
    return top;
}

long long nthSuperUglyNumber(int n, int *primes, int primesSize) {
    if (n <= 0 || primesSize <= 0 || primes == NULL) {
        return -1;
    }

    long long *ugly = (long long *)malloc((size_t)n * sizeof(long long));
    HeapNode *heap = (HeapNode *)malloc((size_t)primesSize * sizeof(HeapNode));

    if (ugly == NULL || heap == NULL) {
        free(ugly);
        free(heap);
        return -1;
    }

    int heapSize = 0;
    ugly[0] = 1;

    for (int i = 0; i < primesSize; ++i) {
        HeapNode node;
        node.value = (long long)primes[i] * ugly[0];
        node.prime = primes[i];
        node.index = 0;
        heapPush(heap, &heapSize, node);
    }

    for (int i = 1; i < n; ++i) {
        long long next = heap[0].value;
        ugly[i] = next;

        while (heapSize > 0 && heap[0].value == next) {
            HeapNode node = heapPop(heap, &heapSize);
            node.index++;
            node.value = (long long)node.prime * ugly[node.index];
            heapPush(heap, &heapSize, node);
        }
    }

    long long result = ugly[n - 1];
    free(ugly);
    free(heap);
    return result;
}

int main(void) {
    int primes[] = {2, 7, 13, 19};
    int n = 12;
    int primesSize = (int)(sizeof(primes) / sizeof(primes[0]));

    printf("%lld\n", nthSuperUglyNumber(n, primes, primesSize));

    return 0;
}