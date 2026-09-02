#include <stdio.h>
#include <stdbool.h>

bool is_min_heap(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return false;
    }
    for (int i = 0; i <= (n - 2) / 2; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && arr[i] > arr[left]) {
            return false;
        }
        if (right < n && arr[i] > arr[right]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int heap1[] = {1, 3, 5, 7, 9, 8, 10};
    int n1 = sizeof(heap1) / sizeof(heap1[0]);
    int heap2[] = {10, 3, 5, 7, 9, 8, 1};
    int n2 = sizeof(heap2) / sizeof(heap2[0]);
    int heap3[] = {5};
    int n3 = sizeof(heap3) / sizeof(heap3[0]);
    int heap4[] = {5, 3};
    int n4 = sizeof(heap4) / sizeof(heap4[0]);
    int heap5[] = {3, 5};
    int n5 = sizeof(heap5) / sizeof(heap5[0]);

    printf("%d\n", is_min_heap(heap1, n1));
    printf("%d\n", is_min_heap(heap2, n2));
    printf("%d\n", is_min_heap(heap3, n3));
    printf("%d\n", is_min_heap(heap4, n4));
    printf("%d\n", is_min_heap(heap5, n5));

    return 0;
}