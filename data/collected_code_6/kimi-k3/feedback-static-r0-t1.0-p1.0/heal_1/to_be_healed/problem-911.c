#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  'strerror' is defined in header '<string.h>'; this is probably fixable by adding '#include <string.h>'
  */

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} MinHeap;

static void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void min_heapify_up(MinHeap *heap, size_t idx)
{
    while (idx > 0) {
        size_t parent = (idx - 1) / 2;
        if (heap->data[parent] <= heap->data[idx]) {
            break;
        }
        swap(&heap->data[parent], &heap->data[idx]);
        idx = parent;
    }
}

static void min_heapify_down(MinHeap *heap, size_t idx)
{
    for (;;) {
        size_t left = 2 * idx + 1;
        size_t right = 2 * idx + 2;
        size_t smallest = idx;

        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }
        if (smallest == idx) {
            break;
        }
        swap(&heap->data[idx], &heap->data[smallest]);
        idx = smallest;
    }
}

static int min_heap_push(MinHeap *heap, int value)
{
    if (heap->size >= heap->capacity) {
        return -1;
    }
    heap->data[heap->size] = value;
    min_heapify_up(heap, heap->size);
    heap->size++;
    return 0;
}

static int min_heap_pop(MinHeap *heap, int *value)
{
    if (heap->size == 0) {
        return -1;
    }
    *value = heap->data[0];
    heap->size--;
    if (heap->size > 0) {
        heap->data[0] = heap->data[heap->size];
        min_heapify_down(heap, 0);
    }
    return 0;
}

static int min_heap_peek(const MinHeap *heap, int *value)
{
    if (heap->size == 0) {
        return -1;
    }
    *value = heap->data[0];
    return 0;
}

static void max_heapify_down(int *arr, size_t n, size_t idx)
{
    for (;;) {
        size_t left = 2 * idx + 1;
        size_t right = 2 * idx + 2;
        size_t largest = idx;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
        if (largest == idx) {
            break;
        }
        swap(&arr[idx], &arr[largest]);
        idx = largest;
    }
}

static void max_heapify_up(int *arr, size_t idx)
{
    while (idx > 0) {
        size_t parent = (idx - 1) / 2;
        if (arr[parent] >= arr[idx]) {
            break;
        }
        swap(&arr[parent], &arr[idx]);
        idx = parent;
    }
}

static int max_heap_push(int *arr, size_t *size, int value)
{
    arr[*size] = value;
    max_heapify_up(arr, *size);
    (*size)++;
    return 0;
}

static int max_heap_pop(int *arr, size_t *size, int *value)
{
    if (*size == 0) {
        return -1;
    }
    *value = arr[0];
    (*size)--;
    if (*size > 0) {
        arr[0] = arr[*size];
        max_heapify_down(arr, *size, 0);
    }
    return 0;
}

int maximum_product_of_three(const int *arr, size_t n, long long *result)
{
    if (arr == NULL || result == NULL || n < 3) {
        errno = EINVAL;
        return -1;
    }

    int *min_data = (int *)malloc(3 * sizeof(int));
    if (min_data == NULL) {
        errno = ENOMEM;
        return -1;
    }

    int *max_data = (int *)malloc(2 * sizeof(int));
    if (max_data == NULL) {
        free(min_data);
        errno = ENOMEM;
        return -1;
    }

    MinHeap min_heap = {min_data, 0, 3};
    size_t max_heap_size = 0;

    for (size_t i = 0; i < n; i++) {
        if (min_heap.size < 3) {
            if (min_heap_push(&min_heap, arr[i]) != 0) {
                free(min_data);
                free(max_data);
                errno = ENOMEM;
                return -1;
            }
        } else {
            int top;
            if (min_heap_peek(&min_heap, &top) != 0) {
                free(min_data);
                free(max_data);
                errno = EIO;
                return -1;
            }
            if (arr[i] > top) {
                int dummy;
                if (min_heap_pop(&min_heap, &dummy) != 0) {
                    free(min_data);
                    free(max_data);
                    errno = EIO;
                    return -1;
                }
                if (min_heap_push(&min_heap, arr[i]) != 0) {
                    free(min_data);
                    free(max_data);
                    errno = ENOMEM;
                    return -1;
                }
            }
        }

        /* Possible weaknesses found:
         *  Assuming that condition 'max_heap_size<2' is not redundant
         */
        if (max_heap_size < 2) {
            /* Possible weaknesses found:
             *  Condition 'max_heap_push(max_data,&max_heap_size,arr[i])!=0' is always false
             *  Calling function 'max_heap_push' returns 0
             *  Condition 'max_heap_push(max_data,&max_heap_size,arr[i])!=0' is always false [knownConditionTrueFalse]
             */
            if (max_heap_push(max_data, &max_heap_size, arr[i]) != 0) {
                free(min_data);
                free(max_data);
                errno = ENOMEM;
                return -1;
            }
        } else {
            /* Possible weaknesses found:
             *  Condition 'max_heap_size==0' is always false
             *  Condition 'max_heap_size==0' is always false [knownConditionTrueFalse]
             */
            if (max_heap_size == 0) {
                free(min_data);
                free(max_data);
                errno = EIO;
                return -1;
            }
            if (arr[i] < max_data[0]) {
                int dummy;
                if (max_heap_pop(max_data, &max_heap_size, &dummy) != 0) {
                    free(min_data);
                    free(max_data);
                    errno = EIO;
                    return -1;
                }
                /* Possible weaknesses found:
                 *  Condition 'max_heap_push(max_data,&max_heap_size,arr[i])!=0' is always false
                 *  Calling function 'max_heap_push' returns 0
                 *  Condition 'max_heap_push(max_data,&max_heap_size,arr[i])!=0' is always false [knownConditionTrueFalse]
                 */
                if (max_heap_push(max_data, &max_heap_size, arr[i]) != 0) {
                    free(min_data);
                    free(max_data);
                    errno = ENOMEM;
                    return -1;
                }
            }
        }
    }

    int max1, max2, max3;
    if (min_heap_pop(&min_heap, &max3) != 0 ||
        min_heap_pop(&min_heap, &max2) != 0 ||
        min_heap_pop(&min_heap, &max1) != 0) {
        free(min_data);
        free(max_data);
        errno = EIO;
        return -1;
    }

    int min1, min2;
    if (max_heap_pop(max_data, &max_heap_size, &min2) != 0 ||
        max_heap_pop(max_data, &max_heap_size, &min1) != 0) {
        free(min_data);
        free(max_data);
        errno = EIO;
        return -1;
    }

    long long product1 = (long long)max1 * (long long)max2 * (long long)max3;
    long long product2 = (long long)min1 * (long long)min2 * (long long)max1;

    *result = (product1 > product2) ? product1 : product2;

    free(min_data);
    free(max_data);
    return 0;
}

int main(void)
{
    int arr[] = {-10, -10, 5, 2, 3, -1};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long long result;

    if (maximum_product_of_three(arr, n, &result) != 0) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'strerror' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strerror'
         *  call to undeclared library function 'strerror' with type 'char *(int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("Maximum product of three numbers: %lld\n", result);
    return EXIT_SUCCESS;
}