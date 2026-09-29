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
    while (i > 0 && h->data[(i - 1) / 2].value > h->data[i].value) {
        swap(&h->data[(i - 1) / 2], &h->data[i]);
        i = (i - 1) / 2;
    }
}

Node heap_pop(Heap *h) {
    Node root = h->data[0];
    h->size--;
    h->data[0] = h->data[h->size];
    int i = 0;
    while (1) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < h->size && h->data[left].value < h->data[smallest].value) {
            smallest = left;
        }
        if (right < h->size && h->data[right].value < h->data[smallest].value) {
            smallest = right;
        }
        if (smallest == i) break;
        swap(&h->data[i], &h->data[smallest]);
        i = smallest;
    }
    return root;
}

long long nthSuperUglyNumber(int n, int const *primes, int k) {
    if (n <= 0 || k <= 0) return 0;
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
        heap_push(&h, (long long)primes[i], i, 1LL);
    }
    
    int count = 1;
    while (count < n) {
        Node top = heap_pop(&h);
        if (top.value != ugly[count - 1]) {
            ugly[count] = top.value;
            count++;
        }
        long long next_val = top.last_value * primes[top.prime_index];
        if (next_val / primes[top.prime_index] == top.last_value) {
            heap_push(&h, next_val, top.prime_index, next_val);
        }
    }
    
    long long result = ugly[n - 1];
    free(ugly);
    free(h.data);
    return result;
}

int main() {
    int primes1[] = {2, 3, 5};
    int k1 = sizeof(primes1) / sizeof(primes1[0]);
    int n1 = 10;
    long long result1 = nthSuperUglyNumber(n1, primes1, k1);
    printf("%lld\n", result1);

    int primes2[] = {2, 7, 13, 19};
    int k2 = sizeof(primes2) / sizeof(primes2[0]);
    int n2 = 12;
    long long result2 = nthSuperUglyNumber(n2, primes2, k2);
    printf("%lld\n", result2);
    
    return 0;
}