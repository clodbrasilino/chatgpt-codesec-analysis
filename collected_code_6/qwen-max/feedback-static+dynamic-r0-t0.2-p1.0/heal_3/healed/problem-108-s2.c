#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *array;
    size_t used;
    size_t size;
} PriorityQueue;

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

PriorityQueue* create_priority_queue(size_t initial_size) {
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->array = (int *)malloc(initial_size * sizeof(int));
    pq->used = 0;
    pq->size = initial_size;
    return pq;
}

void push(PriorityQueue *pq, int value) {
    if (pq->used == pq->size) {
        pq->size *= 2;
        pq->array = (int *)realloc(pq->array, pq->size * sizeof(int));
    }
    pq->array[pq->used++] = value;
    qsort(pq->array, pq->used, sizeof(int), compare);
}

int pop(PriorityQueue *pq) {
    if (pq->used == 0) {
        return INT_MAX;
    }
    return pq->array[--pq->used];
}

void free_priority_queue(PriorityQueue *pq) {
    free(pq->array);
    free(pq);
}

int* merge_sorted_arrays(int **arrays, const int *sizes, int k, int *result_size) {
    PriorityQueue *pq = create_priority_queue(k);
    int *indices = (int *)calloc(k, sizeof(int));
    int *result = NULL;
    int result_capacity = 0;
    *result_size = 0;

    while (1) {
        int min_value = INT_MAX;
        int min_index = -1;

        for (int i = 0; i < k; ++i) {
            if (indices[i] < sizes[i] && arrays[i][indices[i]] < min_value) {
                min_value = arrays[i][indices[i]];
                min_index = i;
            }
        }

        if (min_index == -1) break;

        push(pq, min_value);
        indices[min_index]++;

        if (*result_size >= result_capacity) {
            result_capacity += 16;
            int *new_result = (int *)realloc(result, result_capacity * sizeof(int));
            if (new_result == NULL) {
                free(indices);
                free_priority_queue(pq);
                return NULL;
            }
            result = new_result;
        }
        result[*result_size] = pop(pq);
        (*result_size)++;
    }

    free(indices);
    free_priority_queue(pq);
    return result;
}

int main() {
    int arr1[] = {1, 3, 5};
    int arr2[] = {2, 4, 6};
    int arr3[] = {0, 7, 8, 9};

    int *arrays[] = {arr1, arr2, arr3};
    const int sizes[] = {3, 3, 4};
    int k = 3;

    int result_size;
    int *merged = merge_sorted_arrays(arrays, sizes, k, &result_size);

    for (int i = 0; i < result_size; ++i) {
        printf("%d ", merged[i]);
    }
    printf("\n");

    free(merged);
    return 0;
}