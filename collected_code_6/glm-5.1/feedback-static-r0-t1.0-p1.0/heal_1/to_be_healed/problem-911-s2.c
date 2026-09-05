#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void push_min_heap(int *heap, int *size, int value) {
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

int pop_min_heap(int *heap, int *size) {
    if (*size == 0) return INT_MIN;
    int root = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < *size && heap[left] < heap[smallest]) smallest = left;
        if (right < *size && heap[right] < heap[smallest]) smallest = right;
        if (smallest != i) {
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
    return root;
}

void push_max_heap(int *heap, int *size, int value) {
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

int pop_max_heap(int *heap, int *size) {
    if (*size == 0) return INT_MIN;
    int root = -heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < *size && heap[left] < heap[smallest]) smallest = left;
        if (right < *size && heap[right] < heap[smallest]) smallest = right;
        if (smallest != i) {
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
    return root;
}

/* Possible weaknesses found:
 *  Parameter 'nums' can be declared as pointer to const [constParameterPointer]
 */
long long maximumProduct(int *nums, int numsSize) {
    if (numsSize < 3) return 0;

    int max_heap[3];
    int max_heap_size = 0;

    int min_heap[3];
    int min_heap_size = 0;

    for (int i = 0; i < numsSize; i++) {
        push_max_heap(max_heap, &max_heap_size, nums[i]);
        if (max_heap_size > 3) {
            pop_max_heap(max_heap, &max_heap_size);
        }

        push_min_heap(min_heap, &min_heap_size, nums[i]);
        if (min_heap_size > 3) {
            pop_min_heap(min_heap, &min_heap_size);
        }
    }

    int max1 = pop_max_heap(max_heap, &max_heap_size);
    int max2 = pop_max_heap(max_heap, &max_heap_size);
    int max3 = pop_max_heap(max_heap, &max_heap_size);

    int min1 = pop_min_heap(min_heap, &min_heap_size);
    int min2 = pop_min_heap(min_heap, &min_heap_size);

    long long product1 = (long long)max1 * max2 * max3;
    long long product2 = (long long)max1 * min1 * min2;

    return product1 > product2 ? product1 : product2;
}

int main() {
    int arr1[] = {1, 2, 3, 4};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%lld\n", maximumProduct(arr1, size1));

    int arr2[] = {-10, -10, 5, 2};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%lld\n", maximumProduct(arr2, size2));

    int arr3[] = {-5, -6, -1, -2, -3};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%lld\n", maximumProduct(arr3, size3));

    return 0;
}