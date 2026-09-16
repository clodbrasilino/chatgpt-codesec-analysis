#include <stdio.h>
#include <stdlib.h>

void heapify(int *list, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && list[left] > list[largest])
        largest = left;

    if (right < n && list[right] > list[largest])
        largest = right;

    if (largest != i) {
        int swap = list[i];
        list[i] = list[largest];
        list[largest] = swap;

        heapify(list, n, largest);
    }
}

void buildHeap(int *list, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(list, n, i);
    }
}

int main() {
    int list[] = {3, 5, 2, 7, 8, 1, 4, 6};
    int n = sizeof(list) / sizeof(list[0]);

    buildHeap(list, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }

    return 0;
}