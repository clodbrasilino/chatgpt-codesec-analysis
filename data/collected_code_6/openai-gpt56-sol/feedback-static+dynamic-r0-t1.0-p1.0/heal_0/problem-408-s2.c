#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
    int64_t sum;
} Pair;

typedef struct {
    size_t first_index;
    size_t second_index;
    int64_t sum;
} HeapNode;

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int node_is_less(const HeapNode *left, const HeapNode *right)
{
    if (left->sum != right->sum) {
        return left->sum < right->sum;
    }

    if (left->first_index != right->first_index) {
        return left->first_index < right->first_index;
    }

    return left->second_index < right->second_index;
}

static int heap_push(HeapNode *heap, size_t *heap_size, HeapNode node)
{
    size_t index;

    if (heap == NULL || heap_size == NULL) {
        return -1;
    }

    index = *heap_size;
    heap[index] = node;
    ++(*heap_size);

    while (index > 0U) {
        size_t parent = (index - 1U) / 2U;
        HeapNode temporary;

        if (!node_is_less(&heap[index], &heap[parent])) {
            break;
        }

        temporary = heap[index];
        heap[index] = heap[parent];
        heap[parent] = temporary;
        index = parent;
    }

    return 0;
}

static int heap_pop(HeapNode *heap, size_t *heap_size, HeapNode *result)
{
    size_t index = 0U;

    if (heap == NULL || heap_size == NULL || result == NULL || *heap_size == 0U) {
        return -1;
    }

    *result = heap[0];
    --(*heap_size);

    if (*heap_size == 0U) {
        return 0;
    }

    heap[0] = heap[*heap_size];

    for (;;) {
        size_t left = (index * 2U) + 1U;
        size_t right = left + 1U;
        size_t smallest = index;
        HeapNode temporary;

        if (left < *heap_size && node_is_less(&heap[left], &heap[smallest])) {
            smallest = left;
        }

        if (right < *heap_size && node_is_less(&heap[right], &heap[smallest])) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        temporary = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temporary;
        index = smallest;
    }

    return 0;
}

static int find_k_pairs(const int *first_array,
                        size_t first_length,
                        const int *second_array,
                        size_t second_length,
                        size_t k,
                        Pair **pairs,
                        size_t *pair_count)
{
    int *first_copy = NULL;
    int *second_copy = NULL;
    HeapNode *heap = NULL;
    Pair *result = NULL;
    size_t heap_capacity;
    size_t heap_size = 0U;
    size_t maximum_pairs;
    size_t result_count = 0U;
    size_t index;

    if (pairs == NULL || pair_count == NULL) {
        return -1;
    }

    *pairs = NULL;
    *pair_count = 0U;

    if (k == 0U) {
        return 0;
    }

    if (first_array == NULL || second_array == NULL ||
        first_length == 0U || second_length == 0U) {
        return -1;
    }

    if (first_length > SIZE_MAX / second_length) {
        maximum_pairs = SIZE_MAX;
    } else {
        maximum_pairs = first_length * second_length;
    }

    if (k > maximum_pairs) {
        k = maximum_pairs;
    }

    if (first_length > SIZE_MAX / sizeof(*first_copy) ||
        second_length > SIZE_MAX / sizeof(*second_copy) ||
        k > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    first_copy = malloc(first_length * sizeof(*first_copy));
    second_copy = malloc(second_length * sizeof(*second_copy));
    result = malloc(k * sizeof(*result));

    if (first_copy == NULL || second_copy == NULL || result == NULL) {
        free(first_copy);
        free(second_copy);
        free(result);
        return -1;
    }

    for (index = 0U; index < first_length; ++index) {
        first_copy[index] = first_array[index];
    }

    for (index = 0U; index < second_length; ++index) {
        second_copy[index] = second_array[index];
    }

    qsort(first_copy, first_length, sizeof(*first_copy), compare_ints);
    qsort(second_copy, second_length, sizeof(*second_copy), compare_ints);

    heap_capacity = first_length < k ? first_length : k;

    if (heap_capacity > SIZE_MAX / sizeof(*heap)) {
        free(first_copy);
        free(second_copy);
        free(result);
        return -1;
    }

    heap = malloc(heap_capacity * sizeof(*heap));

    if (heap == NULL) {
        free(first_copy);
        free(second_copy);
        free(result);
        return -1;
    }

    for (index = 0U; index < heap_capacity; ++index) {
        HeapNode node;

        node.first_index = index;
        node.second_index = 0U;
        node.sum = (int64_t)first_copy[index] + (int64_t)second_copy[0];

        if (heap_push(heap, &heap_size, node) != 0) {
            free(heap);
            free(first_copy);
            free(second_copy);
            free(result);
            return -1;
        }
    }

    while (result_count < k && heap_size > 0U) {
        HeapNode node;

        if (heap_pop(heap, &heap_size, &node) != 0) {
            free(heap);
            free(first_copy);
            free(second_copy);
            free(result);
            return -1;
        }

        result[result_count].first = first_copy[node.first_index];
        result[result_count].second = second_copy[node.second_index];
        result[result_count].sum = node.sum;
        ++result_count;
        ++node.second_index;

        if (node.second_index < second_length) {
            node.sum = (int64_t)first_copy[node.first_index] +
                       (int64_t)second_copy[node.second_index];

            if (heap_push(heap, &heap_size, node) != 0) {
                free(heap);
                free(first_copy);
                free(second_copy);
                free(result);
                return -1;
            }
        }
    }

    free(heap);
    free(first_copy);
    free(second_copy);

    *pairs = result;
    *pair_count = result_count;
    return 0;
}

int main(void)
{
    int first_array[] = {1, 7, 11};
    int second_array[] = {2, 4, 6};
    const size_t first_length = sizeof(first_array) / sizeof(first_array[0]);
    const size_t second_length = sizeof(second_array) / sizeof(second_array[0]);
    const size_t k = 5U;
    Pair *pairs = NULL;
    size_t pair_count = 0U;
    size_t index;

    if (find_k_pairs(first_array,
                     first_length,
                     second_array,
                     second_length,
                     k,
                     &pairs,
                     &pair_count) != 0) {
        fputs("Failed to find pairs.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0U; index < pair_count; ++index) {
        if (printf("(%d, %d) sum=%lld\n",
                   pairs[index].first,
                   pairs[index].second,
                   (long long)pairs[index].sum) < 0) {
            free(pairs);
            return EXIT_FAILURE;
        }
    }

    free(pairs);

    if (ferror(stdout)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}