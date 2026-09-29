#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sift_down(int *arr, int n, int i) {
    /* Possible weaknesses found:
     *  The scope of the variable 'left' can be reduced. [variableScope]
     *  The scope of the variable 'largest' can be reduced. [variableScope]
     *  The scope of the variable 'right' can be reduced. [variableScope]
     */
    int largest, left, right;
    while (1) {
        largest = i;
        left = 2 * i + 1;
        right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest == i) {
            break;
        }

        swap(&arr[i], &arr[largest]);
        i = largest;
    }
}

void build_heap(int *arr, int n) {
    if (arr == NULL || n <= 1) {
        return;
    }

    for (int i = n / 2 - 1; i >= 0; i--) {
        sift_down(arr, n, i);
    }
}

int main(void) {
    int arr[] = {4, 10, 3, 5, 1, 8, 9, 2, 6, 7};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    build_heap(arr, n);

    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}