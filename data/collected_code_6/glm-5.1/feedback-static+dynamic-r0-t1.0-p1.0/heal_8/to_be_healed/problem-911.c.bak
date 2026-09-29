#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void push_min(int **heap, int *size, int *capacity, int value) {
    if (*size >= *capacity) {
        *capacity *= 2;
        *heap = (int *)realloc(*heap, *capacity * sizeof(int));
    }
    (*heap)[*size] = value;
    int i = *size;
    (*size)++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if ((*heap)[parent] > (*heap)[i]) {
            int temp = (*heap)[parent];
            (*heap)[parent] = (*heap)[i];
            (*heap)[i] = temp;
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
            int temp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }
    return min_val;
}

void push_max(int **heap, int *size, int *capacity, int value) {
    if (*size >= *capacity) {
        *capacity *= 2;
        *heap = (int *)realloc(*heap, *capacity * sizeof(int));
    }
    (*heap)[*size] = -value;
    int i = *size;
    (*size)++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if ((*heap)[parent] > (*heap)[i]) {
            int temp = (*heap)[parent];
            (*heap)[parent] = (*heap)[i];
            (*heap)[i] = temp;
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
            int temp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }
    return max_val;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 414375, got <no output>
  *  test case 0 failed: expected 225700, got <no output>
  *  test case 2 failed: expected 2520, got <no output>
  */

int maximumProduct(const int *nums, int numsSize) {
    if (numsSize < 3) {
        return 0;
    }
    
    int min_capacity = 4;
    int *min_heap = (int *)malloc(min_capacity * sizeof(int));
    if (!min_heap) {
        return 0;
    }
    int min_size = 0;
    
    int max_capacity = 4;
    int *max_heap = (int *)malloc(max_capacity * sizeof(int));
    if (!max_heap) {
        free(min_heap);
        return 0;
    }
    int max_size = 0;

    for (int i = 0; i < numsSize; i++) {
        push_max(&max_heap, &max_size, &max_capacity, nums[i]);
        if (max_size > 3) {
            pop_min(max_heap, &max_size);
        }

        push_min(&min_heap, &min_size, &min_capacity, nums[i]);
        if (min_size > 2) {
            pop_max(min_heap, &min_size);
        }
    }

    int max1 = -pop_min(max_heap, &max_size);
    int max2 = -pop_min(max_heap, &max_size);
    int max3 = -pop_min(max_heap, &max_size);

    int min1 = pop_max(min_heap, &min_size);
    int min2 = pop_max(min_heap, &min_size);

    long long product1 = (long long)min1 * min2;
    long long res1 = product1 * max3;
    
    long long product2 = (long long)max1 * max2;
    long long res2 = product2 * max3;

    long long max_res = res1 > res2 ? res1 : res2;

    free(min_heap);
    free(max_heap);

    if (max_res > INT_MAX) {
        return INT_MAX;
    }
    return (int)max_res;
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