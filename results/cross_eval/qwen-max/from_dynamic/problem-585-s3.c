#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

void heapify(float *prices, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && prices[left] > prices[largest])
        largest = left;

    if (right < n && prices[right] > prices[largest])
        largest = right;

    if (largest != i) {
        float temp = prices[i];
        prices[i] = prices[largest];
        prices[largest] = temp;

        heapify(prices, n, largest);
    }
}

void buildMaxHeap(float *prices, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(prices, n, i);
}

void findNExpensiveItems(float *prices, int n, int count) {
    buildMaxHeap(prices, n);

    for (int i = 0; i < count; i++) {
        printf("%.2f\n", prices[0]);
        prices[0] = prices[n - i - 1];
        heapify(prices, n - i - 1, 0);
    }
}

int main() {
    float prices[] = {10.0, 8.5, 9.3, 7.6, 5.5, 6.0, 7.0, 8.0, 9.0, 10.5};
    int n = sizeof(prices) / sizeof(prices[0]);
    int count = 3;

    findNExpensiveItems(prices, n, count);

    return 0;
}