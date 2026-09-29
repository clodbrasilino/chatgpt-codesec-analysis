#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef int heap_elem_t;

static void heap_swap(heap_elem_t *a, heap_elem_t *b)
{
    heap_elem_t tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heap_sift_down(heap_elem_t *arr, size_t root, size_t n)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'child' can be reduced. [variableScope]
     */
    size_t child;
    /* Possible weaknesses found:
     *  The scope of the variable 'largest' can be reduced. [variableScope]
     */
    size_t largest;

    while (root < n) {
        child = 2u * root + 1u;
        if (child < root || child >= n) {
            break;
        }
        largest = root;
        if (arr[largest] < arr[child]) {
            largest = child;
        }
        if (child + 1u < n && arr[largest] < arr[child + 1u]) {
            largest = child + 1u;
        }
        if (largest == root) {
            break;
        }
        heap_swap(&arr[root], &arr[largest]);
        root = largest;
    }
}

int heap_build(heap_elem_t *arr, size_t n)
{
    size_t i;

    if (arr == NULL && n > 0u) {
        return -1;
    }
    if (n < 2u) {
        return 0;
    }

    i = n / 2u;
    while (i > 0u) {
        i--;
        heap_sift_down(arr, i, n);
    }

    return 0;
}

static int heap_verify(const heap_elem_t *arr, size_t n)
{
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'left' can be reduced. [variableScope]
     */
    size_t left;
    /* Possible weaknesses found:
     *  The scope of the variable 'right' can be reduced. [variableScope]
     */
    size_t right;

    for (i = 0u; i < n; i++) {
        left = 2u * i + 1u;
        right = 2u * i + 2u;
        if (left < i || right < i) {
            break;
        }
        if (left < n && arr[i] < arr[left]) {
            return 0;
        }
        if (right < n && arr[i] < arr[right]) {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    static const heap_elem_t input[] = { 9, 4, 7, 1, 8, 3, 6, 2, 5, 0 };
    const size_t n = sizeof(input) / sizeof(input[0]);
    heap_elem_t *heap;
    size_t i;

    heap = malloc(n * sizeof(*heap));
    if (heap == NULL) {
        fprintf(stderr, "error: out of memory\n");
        return EXIT_FAILURE;
    }

    for (i = 0u; i < n; i++) {
        heap[i] = input[i];
    }

    if (heap_build(heap, n) != 0) {
        fprintf(stderr, "error: heap construction failed\n");
        free(heap);
        heap = NULL;
        return EXIT_FAILURE;
    }

    if (heap_verify(heap, n) == 0) {
        fprintf(stderr, "error: heap property violation\n");
        free(heap);
        heap = NULL;
        return EXIT_FAILURE;
    }

    printf("heapified array:");
    for (i = 0u; i < n; i++) {
        printf(" %d", heap[i]);
    }
    putchar('\n');

    free(heap);
    heap = NULL;

    return EXIT_SUCCESS;
}