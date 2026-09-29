#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(int heap[], int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] < heap[smallest]) {
        smallest = left;
    }
    if (right < size && heap[right] < heap[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        min_heapify(heap, size, smallest);
    }
}

void max_heapify(int heap[], int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] > heap[largest]) {
        largest = left;
    }
    if (right < size && heap[right] > heap[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        max_heapify(heap, size, largest);
    }
}

int maxProduct(int nums[], int numsSize) {
    if (numsSize < 3) {
        return 0;
    }

    int top3[3] = {INT_MIN, INT_MIN, INT_MIN};
    int bottom2[2] = {INT_MAX, INT_MAX};

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > top3[0]) {
            top3[0] = nums[i];
            min_heapify(top3, 3, 0);
        }
        if (nums[i] < bottom2[0]) {
            bottom2[0] = nums[i];
            max_heapify(bottom2, 2, 0);
        }
    }

    int prod1 = top3[0] * top3[1] * top3[2];
    int prod2 = bottom2[0] * bottom2[1] * (top3[0] > top3[1] ? (top3[0] > top3[2] ? top3[0] : top3[2]) : (top3[1] > top3[2] ? top3[1] : top3[2]));

    int max_val = top3[0];
    if (top3[1] > max_val) max_val = top3[1];
    if (top3[2] > max_val) max_val = top3[2];

    prod2 = bottom2[0] * bottom2[1] * max_val;

    return prod1 > prod2 ? prod1 : prod2;
}

int main() {
    int nums[] = {-10, -10, 5, 2};
    int size = sizeof(nums) / sizeof(nums[0]);
    
    int result = maxProduct(nums, size);
    
    printf("%d\n", result);
    
    return 0;
}