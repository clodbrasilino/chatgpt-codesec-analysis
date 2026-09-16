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
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent] > heap[i]) {
            swap(&heap[parent], &heap[i]);
            i = parent;
        } else {
            break;
        }
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
        if (left < *size && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < *size && heap[right] < heap[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
    return min_val;
}

void push_max(int *heap, int *size, int value) {
    value = -value;
    heap[*size] = value;
    int i = *size;
    (*size)++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent] > heap[i]) {
            swap(&heap[parent], &heap[i]);
            i = parent;
        } else {
            break;
        }
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
        if (left < *size && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < *size && heap[right] < heap[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
    return max_val;
}

int maximumProduct(int *nums, int numsSize) {
    if (numsSize < 3) {
        return 0;
    }
    
    int *min_heap = (int *)malloc(3 * sizeof(int));
    if (!min_heap) {
        return 0;
    }
    int min_size = 0;
    
    int *max_heap = (int *)malloc(2 * sizeof(int));
    if (!max_heap) {
        free(min_heap);
        return 0;
    }
    int max_size = 0;

    for (int i = 0; i < numsSize; i++) {
        push_min(min_heap, &min_size, nums[i]);
        if (min_size > 3) {
            pop_min(min_heap, &min_size);
        }

        push_max(max_heap, &max_size, nums[i]);
        if (max_size > 2) {
            pop_max(max_heap, &max_size);
        }
    }

    int max1 = pop_max(max_heap, &max_size);
    int max2 = pop_max(max_heap, &max_size);

    int min1 = pop_min(min_heap, &min_size);
    int min2 = pop_min(min_heap, &min_size);
    int min3 = pop_min(min_heap, &min_size);

    long long product1 = (long long)max1 * max2;
    long long product2 = (long long)min1 * min2;

    int result;
    if (product1 > product2) {
        if (__builtin_mul_overflow(product1, min3, &result)) {
            result = INT_MAX;
        }
    } else {
        if (__builtin_mul_overflow(product2, max1, &result)) {
            result = INT_MAX;
        }
    }

    free(min_heap);
    free(max_heap);

    return result;
}

int main() {
    int nums1[] = {1, 2, 3, 4};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    printf("%d\n", maximumProduct(nums1, size1));

    int nums2[] = {-10, -10, 5, 2};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    printf("%d\n", maximumProduct(nums2, size2));

    int nums3[] = {-1, -2, -3};
    int size3 = sizeof(nums3) / sizeof(nums3[0]);
    printf("%d\n", maximumProduct(nums3, size3));

    return 0;
}