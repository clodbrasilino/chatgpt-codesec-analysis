#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static void swap_int(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void sift_down_max(int *heap, size_t size, size_t root)
{
    for (;;) {
        size_t largest = root;
        size_t left = 2u * root + 1u;
        size_t right = 2u * root + 2u;

        if (left < size && heap[left] > heap[largest]) {
            largest = left;
        }
        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }
        if (largest == root) {
            break;
        }
        swap_int(&heap[root], &heap[largest]);
        root = largest;
    }
}

static void sift_down_min(int *heap, size_t size, size_t root)
{
    for (;;) {
        size_t smallest = root;
        size_t left = 2u * root + 1u;
        size_t right = 2u * root + 2u;

        if (left < size && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < size && heap[right] < heap[smallest]) {
            smallest = right;
        }
        if (smallest == root) {
            break;
        }
        swap_int(&heap[root], &heap[smallest]);
        root = smallest;
    }
}

static void build_max_heap(int *heap, size_t size)
{
    size_t i = size / 2u;

    while (i > 0u) {
        i--;
        sift_down_max(heap, size, i);
    }
}

static void build_min_heap(int *heap, size_t size)
{
    size_t i = size / 2u;

    while (i > 0u) {
        i--;
        sift_down_min(heap, size, i);
    }
}

static int pop_max(int *heap, size_t *size)
{
    int top = heap[0];

    (*size)--;
    heap[0] = heap[*size];
    sift_down_max(heap, *size, 0u);
    return top;
}

static int pop_min(int *heap, size_t *size)
{
    int top = heap[0];

    (*size)--;
    heap[0] = heap[*size];
    sift_down_min(heap, *size, 0u);
    return top;
}

static int max_product_of_three(const int *arr, size_t n, long long *result)
{
    int *heap;
    size_t heap_size;
    size_t i;
    long long l1;
    long long l2;
    long long l3;
    long long s1;
    long long s2;
    long long candidate1;
    long long candidate2;

    if (arr == NULL || result == NULL || n < 3u) {
        return -1;
    }
    if (n > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    heap = malloc(n * sizeof(int));
    if (heap == NULL) {
        return -1;
    }

    for (i = 0u; i < n; i++) {
        heap[i] = arr[i];
    }

    heap_size = n;
    build_max_heap(heap, heap_size);
    l1 = (long long)pop_max(heap, &heap_size);
    l2 = (long long)pop_max(heap, &heap_size);
    l3 = (long long)pop_max(heap, &heap_size);

    for (i = 0u; i < n; i++) {
        heap[i] = arr[i];
    }

    heap_size = n;
    build_min_heap(heap, heap_size);
    s1 = (long long)pop_min(heap, &heap_size);
    s2 = (long long)pop_min(heap, &heap_size);

    free(heap);

    candidate1 = l1 * l2 * l3;
    candidate2 = s1 * s2 * l1;

    *result = (candidate1 > candidate2) ? candidate1 : candidate2;
    return 0;
}

int main(void)
{
    int arr1[] = { 1, 10, 2, 6, 5, 3 };
    int arr2[] = { -10, -10, 5, 2 };
    int arr3[] = { -1, -2, -3, -4 };
    long long result;

    if (max_product_of_three(arr1, sizeof(arr1) / sizeof(arr1[0]), &result) == 0) {
        printf("Max product 1: %lld\n", result);
    } else {
        fprintf(stderr, "Error computing max product 1\n");
        return EXIT_FAILURE;
    }

    if (max_product_of_three(arr2, sizeof(arr2) / sizeof(arr2[0]), &result) == 0) {
        printf("Max product 2: %lld\n", result);
    } else {
        fprintf(stderr, "Error computing max product 2\n");
        return EXIT_FAILURE;
    }

    if (max_product_of_three(arr3, sizeof(arr3) / sizeof(arr3[0]), &result) == 0) {
        printf("Max product 3: %lld\n", result);
    } else {
        fprintf(stderr, "Error computing max product 3\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}