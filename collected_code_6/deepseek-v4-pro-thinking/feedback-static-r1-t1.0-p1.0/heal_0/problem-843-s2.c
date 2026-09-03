#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

typedef struct {
    int64_t value;
    int prime_index;
    int ugly_index;
} HeapNode;

static void heap_swap(HeapNode *a, HeapNode *b) {
    HeapNode tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heap_sift_up(HeapNode *heap, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[parent].value <= heap[idx].value) {
            break;
        }
        heap_swap(&heap[parent], &heap[idx]);
        idx = parent;
    }
}

static void heap_sift_down(HeapNode *heap, int size, int idx) {
    while (1) {
        int left = idx * 2 + 1;
        int right = idx * 2 + 2;
        int smallest = idx;

        if (left < size && heap[left].value < heap[smallest].value) {
            smallest = left;
        }
        if (right < size && heap[right].value < heap[smallest].value) {
            smallest = right;
        }
        if (smallest == idx) {
            break;
        }

        heap_swap(&heap[idx], &heap[smallest]);
        idx = smallest;
    }
}

static void heap_insert(HeapNode *heap, int *size, HeapNode node) {
    int idx = *size;
    heap[idx] = node;
    (*size)++;
    heap_sift_up(heap, idx);
}

static HeapNode heap_extract_min(HeapNode *heap, int *size) {
    HeapNode min = heap[0];
    (*size)--;

    if (*size > 0) {
        heap[0] = heap[*size];
        heap_sift_down(heap, *size, 0);
    }

    return min;
}

int nthSuperUglyNumber(int n, int *primes, int primesSize) {
    if (n <= 0 || primesSize <= 0 || primes == NULL) {
        return -1;
    }

    for (int i = 0; i < primesSize; i++) {
        if (primes[i] <= 1) {
            return -1;
        }
    }

    HeapNode *heap = malloc((size_t)primesSize * sizeof(*heap));
    int64_t *ugly = malloc((size_t)n * sizeof(*ugly));

    if (heap == NULL || ugly == NULL) {
        free(heap);
        free(ugly);
        return -1;
    }

    int heap_size = 0;
    ugly[0] = 1;

    for (int i = 0; i < primesSize; i++) {
        HeapNode node;
        node.value = (int64_t)primes[i];
        node.prime_index = i;
        node.ugly_index = 0;
        heap_insert(heap, &heap_size, node);
    }

    for (int count = 1; count < n; count++) {
        int64_t next = heap[0].value;
        ugly[count] = next;

        while (heap_size > 0 && heap[0].value == next) {
            HeapNode node = heap_extract_min(heap, &heap_size);
            node.ugly_index++;
            node.value = (int64_t)primes[node.prime_index] * ugly[node.ugly_index];
            heap_insert(heap, &heap_size, node);
        }
    }

    if (ugly[n - 1] > INT_MAX) {
        free(heap);
        free(ugly);
        return -1;
    }

    int result = (int)ugly[n - 1];

    free(heap);
    free(ugly);

    return result;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s n prime1 prime2 ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr = NULL;
    errno = 0;
    long n_long = strtol(argv[1], &endptr, 10);

    if (errno == ERANGE || *endptr != '\0' || n_long <= 0 || n_long > INT_MAX) {
        fprintf(stderr, "Invalid n\n");
        return EXIT_FAILURE;
    }

    int n = (int)n_long;
    int primesSize = argc - 2;
    int *primes = malloc((size_t)primesSize * sizeof(*primes));

    if (primes == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < primesSize; i++) {
        errno = 0;
        long p = strtol(argv[i + 2], &endptr, 10);

        if (errno == ERANGE || *endptr != '\0' || p <= 1 || p > INT_MAX) {
            fprintf(stderr, "Invalid prime\n");
            free(primes);
            return EXIT_FAILURE;
        }

        primes[i] = (int)p;
    }

    int result = nthSuperUglyNumber(n, primes, primesSize);
    free(primes);

    if (result < 0) {
        fprintf(stderr, "Error computing super ugly number\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}