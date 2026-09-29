#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void push_min(int *heap, int *size, int value, int capacity) {
    if (*size >= capacity) return;
    heap[*size] = value;
    int i = *size;
    (*size)++;
    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        int temp = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = heap[i];
        heap[i] = temp;
        i = (i - 1) / 2;
    }
}

int pop_min(int *heap, int *size) {
    if (*size <= 0) return 0;
    int min_val = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < *size && heap[left] < heap[smallest]) smallest = left;
        if (right < *size && heap[right] < heap[smallest]) smallest = right;
        if (smallest == i) break;
        int temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        i = smallest;
    }
    return min_val;
}

void push_max(int *heap, int *size, int value, int capacity) {
    if (*size >= capacity) return;
    heap[*size] = -value;
    int i = *size;
    (*size)++;
    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        int temp = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = heap[i];
        heap[i] = temp;
        i = (i - 1) / 2;
    }
}

int pop_max(int *heap, int *size) {
    if (*size <= 0) return 0;
    int max_val = -heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < *size && heap[left] < heap[smallest]) smallest = left;
        if (right < *size && heap[right] < heap[smallest]) smallest = right;
        if (smallest == i) break;
        int temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        i = smallest;
    }
    return max_val;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 414375, got 0
  *  test case 2 failed: expected 2520, got 0
  *  test case 0 failed: expected 225700, got 0
  */

int maximumProduct(const int *nums, int numsSize) {
    if (numsSize < 3) return 0;

    int heap_capacity = 3;
    int *min_heap = malloc(heap_capacity * sizeof(int));
    if (!min_heap) return 0;
    int min_size = 0;

    int *max_heap = malloc(heap_capacity * sizeof(int));
    if (!max_heap) { free(min_heap); return 0; }
    int max_size = 0;

    for (int i = 0; i < numsSize; i++) {
        if (min_size < 3) {
            push_min(min_heap, &min_size, nums[i], heap_capacity);
        } else {
            if (nums[i] > min_heap[0]) {
                pop_min(min_heap, &min_size);
                push_min(min_heap, &min_size, nums[i], heap_capacity);
            }
        }

        if (max_size < 3) {
            push_max(max_heap, &max_size, nums[i], heap_capacity);
        } else {
            if (nums[i] < -max_heap[0]) {
                pop_max(max_heap, &max_size);
                push_max(max_heap, &max_size, nums[i], heap_capacity);
            }
        }
    }

    int min1 = pop_min(min_heap, &min_size);
    int min2 = pop_min(min_heap, &min_size);

    int max3 = pop_max(max_heap, &max_size);
    int max2 = pop_max(max_heap, &max_size);
    int max1 = pop_max(max_heap, &max_size);

    free(min_heap);
    free(max_heap);

    long long product1 = (long long)max1 * max2 * max3;
    long long product2 = (long long)min1 * min2 * max1;
    long long result = product1 > product2 ? product1 : product2;

    if (result > INT_MAX) return INT_MAX;
    if (result < INT_MIN) return INT_MIN;
    return (int)result;
}

int main() {
    int nums1[] = {1, 2, 3, 4};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    printf("%d\n", maximumProduct(nums1, size1));

    int nums2[] = {-10, -10, 5, 2};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    printf("%d\n", maximumProduct(nums2, size2));

    int nums3[] = {-1, -2, -3, -4};
    int size3 = sizeof(nums3) / sizeof(nums3[0]);
    printf("%d\n", maximumProduct(nums3, size3));

    return 0;
}