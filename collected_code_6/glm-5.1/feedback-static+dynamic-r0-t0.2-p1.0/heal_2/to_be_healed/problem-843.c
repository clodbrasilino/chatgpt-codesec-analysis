#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long value;
    int prime_index;
    long long last_value;
} Node;

typedef struct {
    Node *data;
    int capacity;
    int size;
} Heap;

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void heap_push(Heap *h, long long value, int prime_index, long long last_value) {
    if (h->size == h->capacity) {
        h->capacity *= 2;
        h->data = realloc(h->data, h->capacity * sizeof(Node));
        if (!h->data) exit(EXIT_FAILURE);
    }
    h->data[h->size].value = value;
    h->data[h->size].prime_index = prime_index;
    h->data[h->size].last_value = last_value;
    int i = h->size;
    h->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (h->data[parent].value > h->data[i].value) {
            swap(&h->data[parent], &h->data[i]);
            i = parent;
        } else {
            break;
        }
    }
}

Node heap_pop(Heap *h) {
    Node root = h->data[0];
    h->size--;
    h->data[0] = h->data[h->size];
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < h->size && h->data[left].value < h->data[smallest].value) {
            smallest = left;
        }
        if (right < h->size && h->data[right].value < h->data[smallest].value) {
            smallest = right;
        }
        if (smallest != i) {
            swap(&h->data[i], &h->data[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
    return root;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 5408, got <no output>
  *  test case 1 failed: expected 26, got <no output>
  *  test case 0 failed: expected 32, got <no output>
  */

long long nthSuperUglyNumber(int n, const int *primes, int k) {
    if (n <= 0 || !primes || k <= 0) return 0;
    if (n == 1) return 1;
    
    long long *ugly = malloc(n * sizeof(long long));
    if (!ugly) exit(EXIT_FAILURE);
    ugly[0] = 1;
    
    Heap h;
    h.capacity = 16;
    h.size = 0;
    h.data = malloc(h.capacity * sizeof(Node));
    if (!h.data) {
        free(ugly);
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < k; i++) {
        heap_push(&h, (long long)primes[i], i, ugly[0]);
    }
    
    int count = 1;
    while (count < n) {
        Node top = heap_pop(&h);
        if (top.value != ugly[count - 1]) {
            ugly[count] = top.value;
            count++;
        }
        long long next_val = top.last_value * primes[top.prime_index];
        long long next_last = top.value;
        if (next_val / primes[top.prime_index] == top.last_value) {
            heap_push(&h, next_val, top.prime_index, next_last);
        }
    }
    
    long long result = ugly[n - 1];
    free(ugly);
    free(h.data);
    return result;
}

int main() {
    int primes[] = {2, 7, 13, 19};
    int k = sizeof(primes) / sizeof(primes[0]);
    int n = 12;
    long long result = nthSuperUglyNumber(n, primes, k);
    printf("%lld\n", result);
    return 0;
}