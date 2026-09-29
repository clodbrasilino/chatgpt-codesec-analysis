#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void push_min(int *heap, int *size, int value) {
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

void push_max(int *heap, int *size, int value) {
    heap[*size] = value;
    int i = *size;
    (*size)++;
    while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
        int temp = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = heap[i];
        heap[i] = temp;
        i = (i - 1) / 2;
    }
}

int pop_max(int *heap, int *size) {
    int max_val = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        if (left < *size && heap[left] > heap[largest]) largest = left;
        if (right < *size && heap[right] > heap[largest]) largest = right;
        if (largest == i) break;
        int temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;
        i = largest;
    }
    return max_val;
}

int maximumProduct(const int *nums, int numsSize) {
    if (numsSize < 3) return 0;

    int *max_heap = malloc(4 * sizeof(int));
    if (!max_heap) return 0;
    int max_size = 0;

    int *min_heap = malloc(3 * sizeof(int));
    if (!min_heap) { free(max_heap); return 0; }
    int min_size = 0;

    for (int i = 0; i < numsSize; i++) {
        push_max(max_heap, &max_size, nums[i]);
        if (max_size > 3) {
            pop_max(max_heap, &max_size);
        }

        push_min(min_heap, &min_size, nums[i]);
        if (min_size > 2) {
            pop_min(min_heap, &min_size);
        }
    }

    long long max1 = LLONG_MIN;
    long long max2 = LLONG_MIN;
    long long max3 = LLONG_MIN;

    if (max_size > 0) max1 = pop_max(max_heap, &max_size);
    if (max_size > 0) max2 = pop_max(max_heap, &max_size);
    if (max_size > 0) max3 = pop_max(max_heap, &max_size);

    long long min1 = LLONG_MAX;
    long long min2 = LLONG_MAX;

    if (min_size > 0) min1 = pop_min(min_heap, &min_size);
    if (min_size > 0) min2 = pop_min(min_heap, &min_size);

    free(max_heap);
    free(min_heap);

    if (max1 == LLONG_MIN || max2 == LLONG_MIN || max3 == LLONG_MIN) return 0;

    long long product1 = max1 * max2 * max3;
    long long product2 = min1 * min2 * max1;

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