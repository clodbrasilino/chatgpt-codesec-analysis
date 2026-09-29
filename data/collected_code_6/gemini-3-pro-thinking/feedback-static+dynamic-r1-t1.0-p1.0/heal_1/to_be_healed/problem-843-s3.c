#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct HeapNode {
    uint64_t val;
    int p_idx;
    int u_idx;
};

static void heapify_down(struct HeapNode *heap, int size, int idx) {
    while (1) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < size && heap[left].val < heap[smallest].val) {
            smallest = left;
        }
        if (right < size && heap[right].val < heap[smallest].val) {
            smallest = right;
        }
        if (smallest == idx) {
            break;
        }
        
        struct HeapNode temp = heap[idx];
        heap[idx] = heap[smallest];
        heap[smallest] = temp;
        
        idx = smallest;
    }
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 5408, got <no output>
  *  test case 0 failed: expected 32, got <no output>
  *  test case 1 failed: expected 26, got <no output>
  */

uint64_t nth_super_ugly_number(int n, int *primes, int k) {
    if (n <= 0 || k <= 0 || !primes) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    uint64_t *ugly = (uint64_t *)malloc((size_t)n * sizeof(uint64_t));
    if (!ugly) {
        return 0;
    }

    struct HeapNode *heap = (struct HeapNode *)malloc((size_t)k * sizeof(struct HeapNode));
    if (!heap) {
        free(ugly);
        return 0;
    }

    ugly[0] = 1;

    for (int i = 0; i < k; i++) {
        heap[i].val = (uint64_t)primes[i];
        heap[i].p_idx = i;
        heap[i].u_idx = 0;
    }

    for (int i = k / 2 - 1; i >= 0; i--) {
        heapify_down(heap, k, i);
    }

    int count = 1;
    while (count < n) {
        struct HeapNode min_node = heap[0];

        if (min_node.val != ugly[count - 1]) {
            ugly[count] = min_node.val;
            count++;
        }

        int p_idx = min_node.p_idx;
        int next_u_idx = min_node.u_idx + 1;
        uint64_t next_val = (uint64_t)primes[p_idx] * ugly[next_u_idx];

        heap[0].val = next_val;
        heap[0].p_idx = p_idx;
        heap[0].u_idx = next_u_idx;

        heapify_down(heap, k, 0);
    }

    uint64_t result = ugly[n - 1];

    free(heap);
    free(ugly);

    return result;
}

int main(void) {
    int primes[] = {2, 7, 13, 19};
    int k = sizeof(primes) / sizeof(primes[0]);
    int n = 12;

    uint64_t result = nth_super_ugly_number(n, primes, k);
    
    if (result > 0) {
        printf("%llu\n", (unsigned long long)result);
    }

    return 0;
}