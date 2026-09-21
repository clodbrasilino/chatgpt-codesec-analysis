#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define INITIAL_HEAP_CAPACITY ((size_t)16)

typedef struct {
    unsigned long long *data;
    size_t size;
    size_t capacity;
} MinHeap;

static int compareInts(const void *a, const void *b) {
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

static int minHeapInit(MinHeap *heap, size_t capacity) {
    if (capacity == 0) {
        capacity = 1;
    }
    if (capacity > SIZE_MAX / sizeof(*heap->data)) {
        heap->data = NULL;
        heap->size = 0;
        heap->capacity = 0;
        return -1;
    }
    heap->data = (unsigned long long *)malloc(capacity * sizeof(*heap->data));
    if (heap->data == NULL) {
        heap->size = 0;
        heap->capacity = 0;
        return -1;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return 0;
}

static void minHeapDestroy(MinHeap *heap) {
    free(heap->data);
    heap->data = NULL;
    heap->size = 0;
    heap->capacity = 0;
}

static void minHeapSwap(unsigned long long *a, unsigned long long *b) {
    unsigned long long temp = *a;
    *a = *b;
    *b = temp;
}

static void minHeapSiftUp(MinHeap *heap, size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (heap->data[parent] <= heap->data[index]) {
            break;
        }
        minHeapSwap(&heap->data[parent], &heap->data[index]);
        index = parent;
    }
}

static void minHeapSiftDown(MinHeap *heap, size_t index) {
    for (;;) {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t smallest = index;
        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        minHeapSwap(&heap->data[index], &heap->data[smallest]);
        index = smallest;
    }
}

static int minHeapPush(MinHeap *heap, unsigned long long value) {
    if (heap->size == heap->capacity) {
        size_t newCapacity;
        unsigned long long *newData;
        if (heap->capacity > SIZE_MAX / 2) {
            return -1;
        }
        newCapacity = heap->capacity * 2;
        if (newCapacity > SIZE_MAX / sizeof(*heap->data)) {
            return -1;
        }
        newData = (unsigned long long *)realloc(heap->data,
                                                newCapacity * sizeof(*heap->data));
        if (newData == NULL) {
            return -1;
        }
        heap->data = newData;
        heap->capacity = newCapacity;
    }
    heap->data[heap->size] = value;
    heap->size++;
    minHeapSiftUp(heap, heap->size - 1);
    return 0;
}

static unsigned long long minHeapPop(MinHeap *heap) {
    unsigned long long top = heap->data[0];
    heap->size--;
    if (heap->size > 0) {
        heap->data[0] = heap->data[heap->size];
        minHeapSiftDown(heap, 0);
    }
    return top;
}

int nthSuperUglyNumber(int n, const int *primes, int k, unsigned long long *result) {
    int *sortedPrimes;
    int primeCount;
    int i;
    int j;
    size_t primesBytes;
    MinHeap heap;
    unsigned long long current = 0;

    if (n <= 0 || primes == NULL || k <= 0 || result == NULL) {
        return -1;
    }

    if ((size_t)k > SIZE_MAX / sizeof(*sortedPrimes)) {
        return -1;
    }
    primesBytes = (size_t)k * sizeof(*sortedPrimes);

    sortedPrimes = (int *)malloc(primesBytes);
    if (sortedPrimes == NULL) {
        return -1;
    }

    for (i = 0; i < k; i++) {
        if ((size_t)i >= primesBytes / sizeof(*sortedPrimes)) {
            free(sortedPrimes);
            return -1;
        }
        sortedPrimes[i] = primes[i];
    }

    qsort(sortedPrimes, (size_t)k, sizeof(*sortedPrimes), compareInts);

    if (sortedPrimes[0] < 2) {
        free(sortedPrimes);
        return -1;
    }

    primeCount = 0;
    for (i = 0; i < k; i++) {
        if (i == 0 || sortedPrimes[i] != sortedPrimes[i - 1]) {
            sortedPrimes[primeCount] = sortedPrimes[i];
            primeCount++;
        }
    }

    if (minHeapInit(&heap, INITIAL_HEAP_CAPACITY) != 0) {
        free(sortedPrimes);
        return -1;
    }

    if (minHeapPush(&heap, 1ULL) != 0) {
        minHeapDestroy(&heap);
        free(sortedPrimes);
        return -1;
    }

    for (i = 0; i < n; i++) {
        if (heap.size == 0) {
            minHeapDestroy(&heap);
            free(sortedPrimes);
            return -1;
        }
        current = minHeapPop(&heap);
        if (i == n - 1) {
            break;
        }
        for (j = 0; j < primeCount; j++) {
            unsigned long long prime = (unsigned long long)sortedPrimes[j];
            unsigned long long next;
            if (current > ULLONG_MAX / prime) {
                break;
            }
            next = current * prime;
            if (minHeapPush(&heap, next) != 0) {
                minHeapDestroy(&heap);
                free(sortedPrimes);
                return -1;
            }
            if (current % prime == 0ULL) {
                break;
            }
        }
    }

    *result = current;
    minHeapDestroy(&heap);
    free(sortedPrimes);
    return 0;
}

int main(void) {
    int primes[] = {2, 7, 13, 19};
    int k = (int)(sizeof(primes) / sizeof(primes[0]));
    int n = 12;
    unsigned long long result = 0;

    if (nthSuperUglyNumber(n, primes, k, &result) != 0) {
        fprintf(stderr, "Failed to compute the %dth super ugly number\n", n);
        return EXIT_FAILURE;
    }

    printf("The %dth super ugly number is %llu\n", n, result);
    return EXIT_SUCCESS;
}