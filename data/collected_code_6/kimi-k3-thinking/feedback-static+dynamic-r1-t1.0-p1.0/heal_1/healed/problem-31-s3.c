#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int list_index;
    int element_index;
} MergeNode;

typedef struct {
    int frequency;
    int value;
} FreqNode;

typedef struct {
    MergeNode *nodes;
    int size;
    int capacity;
} MergeHeap;

typedef struct {
    FreqNode *nodes;
    int size;
    int capacity;
} FreqHeap;

static void merge_node_swap(MergeNode *a, MergeNode *b)
{
    MergeNode tmp = *a;
    *a = *b;
    *b = tmp;
}

static int merge_heap_init(MergeHeap *heap, int capacity)
{
    if (heap == NULL || capacity <= 0) {
        return -1;
    }
    heap->nodes = (MergeNode *)malloc((size_t)capacity * sizeof(MergeNode));
    if (heap->nodes == NULL) {
        return -1;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return 0;
}

static void merge_heap_free(MergeHeap *heap)
{
    if (heap == NULL) {
        return;
    }
    free(heap->nodes);
    heap->nodes = NULL;
    heap->size = 0;
    heap->capacity = 0;
}

static void merge_heap_sift_up(MergeHeap *heap, int index)
{
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->nodes[parent].value <= heap->nodes[index].value) {
            break;
        }
        merge_node_swap(&heap->nodes[parent], &heap->nodes[index]);
        index = parent;
    }
}

static void merge_heap_sift_down(MergeHeap *heap, int index)
{
    for (;;) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int smallest = index;

        if (left < heap->size &&
            heap->nodes[left].value < heap->nodes[smallest].value) {
            smallest = left;
        }
        if (right < heap->size &&
            heap->nodes[right].value < heap->nodes[smallest].value) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        merge_node_swap(&heap->nodes[smallest], &heap->nodes[index]);
        index = smallest;
    }
}

static int merge_heap_push(MergeHeap *heap, MergeNode node)
{
    if (heap == NULL || heap->size >= heap->capacity) {
        return -1;
    }
    heap->nodes[heap->size] = node;
    merge_heap_sift_up(heap, heap->size);
    heap->size++;
    return 0;
}

static int merge_heap_pop(MergeHeap *heap, MergeNode *out)
{
    if (heap == NULL || out == NULL || heap->size <= 0) {
        return -1;
    }
    *out = heap->nodes[0];
    heap->size--;
    if (heap->size > 0) {
        heap->nodes[0] = heap->nodes[heap->size];
        merge_heap_sift_down(heap, 0);
    }
    return 0;
}

static int merge_heap_peek(const MergeHeap *heap, MergeNode *out)
{
    if (heap == NULL || out == NULL || heap->size <= 0) {
        return -1;
    }
    *out = heap->nodes[0];
    return 0;
}

static int freq_node_less(FreqNode a, FreqNode b)
{
    if (a.frequency != b.frequency) {
        return a.frequency < b.frequency;
    }
    return a.value < b.value;
}

static void freq_node_swap(FreqNode *a, FreqNode *b)
{
    FreqNode tmp = *a;
    *a = *b;
    *b = tmp;
}

static int freq_heap_init(FreqHeap *heap, int capacity)
{
    if (heap == NULL || capacity <= 0) {
        return -1;
    }
    heap->nodes = (FreqNode *)malloc((size_t)capacity * sizeof(FreqNode));
    if (heap->nodes == NULL) {
        return -1;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return 0;
}

static void freq_heap_free(FreqHeap *heap)
{
    if (heap == NULL) {
        return;
    }
    free(heap->nodes);
    heap->nodes = NULL;
    heap->size = 0;
    heap->capacity = 0;
}

static void freq_heap_sift_up(FreqHeap *heap, int index)
{
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (!freq_node_less(heap->nodes[index], heap->nodes[parent])) {
            break;
        }
        freq_node_swap(&heap->nodes[parent], &heap->nodes[index]);
        index = parent;
    }
}

static void freq_heap_sift_down(FreqHeap *heap, int index)
{
    for (;;) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int smallest = index;

        if (left < heap->size &&
            freq_node_less(heap->nodes[left], heap->nodes[smallest])) {
            smallest = left;
        }
        if (right < heap->size &&
            freq_node_less(heap->nodes[right], heap->nodes[smallest])) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        freq_node_swap(&heap->nodes[smallest], &heap->nodes[index]);
        index = smallest;
    }
}

static int freq_heap_push(FreqHeap *heap, FreqNode node)
{
    if (heap == NULL || heap->size >= heap->capacity) {
        return -1;
    }
    heap->nodes[heap->size] = node;
    freq_heap_sift_up(heap, heap->size);
    heap->size++;
    return 0;
}

static void freq_heap_replace_top(FreqHeap *heap, FreqNode node)
{
    if (heap == NULL || heap->size <= 0) {
        return;
    }
    heap->nodes[0] = node;
    freq_heap_sift_down(heap, 0);
}

static int freq_heap_pop(FreqHeap *heap, FreqNode *out)
{
    if (heap == NULL || out == NULL || heap->size <= 0) {
        return -1;
    }
    *out = heap->nodes[0];
    heap->size--;
    if (heap->size > 0) {
        heap->nodes[0] = heap->nodes[heap->size];
        freq_heap_sift_down(heap, 0);
    }
    return 0;
}

int find_top_k_frequent(int **lists, const int *sizes, int num_lists, int k,
                        int *result)
{
    MergeHeap merge_heap;
    FreqHeap top_heap;
    int count = 0;
    int status = -1;
    int merge_ready = 0;
    int freq_ready = 0;

    if (lists == NULL || sizes == NULL || result == NULL) {
        return -1;
    }
    if (num_lists <= 0 || k <= 0) {
        return -1;
    }
    for (int i = 0; i < num_lists; i++) {
        if (sizes[i] < 0) {
            return -1;
        }
        if (sizes[i] > 0 && lists[i] == NULL) {
            return -1;
        }
    }

    if (merge_heap_init(&merge_heap, num_lists) != 0) {
        goto cleanup;
    }
    merge_ready = 1;

    if (freq_heap_init(&top_heap, k) != 0) {
        goto cleanup;
    }
    freq_ready = 1;

    for (int i = 0; i < num_lists; i++) {
        if (sizes[i] > 0) {
            MergeNode node;
            node.value = lists[i][0];
            node.list_index = i;
            node.element_index = 0;
            if (merge_heap_push(&merge_heap, node) != 0) {
                goto cleanup;
            }
        }
    }

    while (merge_heap.size > 0) {
        MergeNode current;
        int value;
        int frequency = 0;

        if (merge_heap_pop(&merge_heap, &current) != 0) {
            goto cleanup;
        }
        value = current.value;
        frequency++;

        {
            int next_index = current.element_index + 1;
            if (next_index < sizes[current.list_index]) {
                MergeNode next;
                next.value = lists[current.list_index][next_index];
                next.list_index = current.list_index;
                next.element_index = next_index;
                if (merge_heap_push(&merge_heap, next) != 0) {
                    goto cleanup;
                }
            }
        }

        for (;;) {
            MergeNode top;
            MergeNode same;
            int next_index;

            if (merge_heap_peek(&merge_heap, &top) != 0 ||
                top.value != value) {
                break;
            }
            if (merge_heap_pop(&merge_heap, &same) != 0) {
                goto cleanup;
            }
            frequency++;
            next_index = same.element_index + 1;
            if (next_index < sizes[same.list_index]) {
                MergeNode next;
                next.value = lists[same.list_index][next_index];
                next.list_index = same.list_index;
                next.element_index = next_index;
                if (merge_heap_push(&merge_heap, next) != 0) {
                    goto cleanup;
                }
            }
        }

        {
            FreqNode candidate;
            candidate.frequency = frequency;
            candidate.value = value;

            if (top_heap.size < k) {
                if (freq_heap_push(&top_heap, candidate) != 0) {
                    goto cleanup;
                }
            } else if (freq_node_less(top_heap.nodes[0], candidate)) {
                freq_heap_replace_top(&top_heap, candidate);
            }
        }
    }

    {
        FreqNode out;
        while (freq_heap_pop(&top_heap, &out) == 0) {
            result[count] = out.value;
            count++;
        }
        for (int i = 0, j = count - 1; i < j; i++, j--) {
            int tmp = result[i];
            result[i] = result[j];
            result[j] = tmp;
        }
    }

    status = count;

cleanup:
    if (freq_ready) {
        freq_heap_free(&top_heap);
    }
    if (merge_ready) {
        merge_heap_free(&merge_heap);
    }
    return status;
}

int main(void)
{
    int list1[] = {1, 4, 5, 8, 10};
    int list2[] = {2, 4, 5, 7, 10};
    int list3[] = {1, 3, 5, 9, 10};
    int list4[] = {4, 6, 8, 10, 12};

    int *lists[] = {list1, list2, list3, list4};
    const int sizes[] = {5, 5, 5, 5};
    const int num_lists = 4;
    const int k = 3;
    int count;
    int *result;

    result = (int *)malloc((size_t)k * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    count = find_top_k_frequent(lists, sizes, num_lists, k, result);
    if (count < 0) {
        fprintf(stderr, "Failed to compute top %d frequent integers.\n", k);
        free(result);
        return EXIT_FAILURE;
    }

    printf("Top %d most frequent integers:\n", k);
    for (int i = 0; i < count; i++) {
        printf("%d\n", result[i]);
    }

    free(result);
    return EXIT_SUCCESS;
}