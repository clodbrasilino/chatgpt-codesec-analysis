#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void push_min(int *heap, int *size, int value) {
    heap[*size] = value;
    int i = *size;
    (*size)++;
    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        swap(&heap[(i - 1) / 2], &heap[i]);
        i = (i - 1) / 2;
    }
}

int pop_min(int *heap, int *size) {
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
        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }
    return min_val;
}

void push_max(int *heap, int *size, int value) {
    value = -value;
    heap[*size] = value;
    int i = *size;
    (*size)++;
    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        swap(&heap[(i - 1) / 2], &heap[i]);
        i = (i - 1) / 2;
    }
}

int pop_max(int *heap, int *size) {
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
        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }
    return max_val;
}

int maximumProduct(const int *nums, int numsSize) {
    if (numsSize < 3) return 0;
    
    int *max_heap = malloc(3 * sizeof(int));
    if (!max_heap) return 0;
    int max_size = 0;

    int *min_heap = malloc(2 * sizeof(int));
    if (!min_heap) { free(max_heap); return 0; }
    int min_size = 0;

    for (int i = 0; i < numsSize; i++) {
        if (max_size < 3) {
            push_max(max_heap, &max_size, nums[i]);
        } else {
            if (nums[i] > -max_heap[0]) {
                pop_max(max_heap, &max_size);
                push_max(max_heap, &max_size, nums[i]);
            }
        }

        if (min_size < 2) {
            push_min(min_heap, &min_size, nums[i]);
        } else {
            if (nums[i] < min_heap[0]) {
                pop_min(min_heap, &min_size);
                push_min(min_heap, &min_size, nums[i]);
            }
        }
    }

    int max1 = pop_max(max_heap, &max_size);
    int max2 = pop_max(max_heap, &max_size);
    int max3 = pop_max(max_heap, &max_size);

    int min1 = pop_min(min_heap, &min_size);
    int min2 = pop_min(min_heap, &min_size);

    free(max_heap);
    free(min_heap);

    long long product1 = (long long)max2 * max3;
    long long product2 = (long long)min1 * min2;
    long long result = (product1 > product2 ? product1 : product2) * max1;

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