#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

typedef struct {
    int* array;
    int capacity;
    int count;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->array = (int*)malloc(capacity * sizeof(int));
    minHeap->capacity = capacity;
    minHeap->count = 0;
    return minHeap;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->count && minHeap->array[left] < minHeap->array[smallest])
        smallest = left;
    if (right < minHeap->count && minHeap->array[right] < minHeap->array[smallest])
        smallest = right;

    if (smallest != idx) {
        swap(&minHeap->array[idx], &minHeap->array[smallest]);
        heapify(minHeap, smallest);
    }
}

void insertKey(MinHeap* minHeap, int key) {
    if (minHeap->count == minHeap->capacity)
        return;

    int i = minHeap->count;
    minHeap->array[i] = key;
    minHeap->count++;
    while (i != 0 && minHeap->array[(i - 1) / 2] > minHeap->array[i]) {
        swap(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int extractMin(MinHeap* minHeap) {
    if (minHeap->count <= 0)
        /* Possible weaknesses found:
         *  'INT_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'INT_MAX'
         *  each undeclared identifier is reported only once for each function it appears in
         */
        return INT_MAX;
    if (minHeap->count == 1) {
        minHeap->count--;
        return minHeap->array[0];
    }

    int root = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->count - 1];
    minHeap->count--;
    heapify(minHeap, 0);

    return root;
}

/* Possible weaknesses found:
 *  Parameter 'uglyNumbers' can be declared as pointer to const [constParameterPointer]
 */
bool isUglyPresent(long long ugly, int k, long long* uglyNumbers) {
    for (int i = 0; i < k; i++) {
        if (ugly == uglyNumbers[i])
            return true;
    }
    return false;
}

/* Possible weaknesses found:
 *  Parameter 'primes' can be declared as pointer to const [constParameterPointer]
 */
long long nthSuperUglyNumber(int n, int* primes, int k) {
    if (n == 1)
        return 1;

    long long* uglyNumbers = (long long*)malloc(n * sizeof(long long));
    MinHeap* minHeap = createMinHeap(n * k);
    uglyNumbers[0] = 1;
    insertKey(minHeap, 1);

    for (int i = 1; i < n; i++) {
        uglyNumbers[i] = extractMin(minHeap);
        for (int j = 0; j < k; j++) {
            long long nextUgly = uglyNumbers[i] * primes[j];
            if (!isUglyPresent(nextUgly, minHeap->count, uglyNumbers)) {
                insertKey(minHeap, nextUgly);
            }
        }
    }

    free(uglyNumbers);
    free(minHeap->array);
    free(minHeap);

    return uglyNumbers[n - 1];
}

int main() {
    int primes[] = {2, 3, 5};
    int k = 3;
    int n = 12;
    long long result = nthSuperUglyNumber(n, primes, k);
    printf("The %dth super ugly number is: %lld\n", n, result);
    return 0;
}