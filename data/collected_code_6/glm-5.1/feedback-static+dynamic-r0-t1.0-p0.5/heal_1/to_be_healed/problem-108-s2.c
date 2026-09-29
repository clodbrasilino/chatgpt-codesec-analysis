#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t len;
    size_t pos;
} Input;

typedef struct {
    int value;
    size_t source_index;
} HeapNode;

typedef struct {
    HeapNode *heap;
    size_t heap_size;
    Input *inputs;
    size_t num_inputs;
} MergeIterator;

void heap_swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heap_sift_down(HeapNode *heap, size_t size, size_t root) {
    size_t smallest = root;
    size_t left = 2 * root + 1;
    size_t right = 2 * root + 2;

    if (left < size && heap[left].value < heap[smallest].value) {
        smallest = left;
    }
    if (right < size && heap[right].value < heap[smallest].value) {
        smallest = right;
    }
    if (smallest != root) {
        heap_swap(&heap[root], &heap[smallest]);
        heap_sift_down(heap, size, smallest);
    }
}

void heap_sift_up(HeapNode *heap, size_t root) {
    if (root == 0) return;
    size_t parent = (root - 1) / 2;
    if (heap[root].value < heap[parent].value) {
        heap_swap(&heap[root], &heap[parent]);
        heap_sift_up(heap, parent);
    }
}

bool merge_iterator_init(MergeIterator *it, Input *inputs, size_t num_inputs) {
    if (it == NULL || inputs == NULL) {
        return false;
    }
    it->inputs = inputs;
    it->num_inputs = num_inputs;
    it->heap_size = 0;
    it->heap = (HeapNode *)malloc(num_inputs * sizeof(HeapNode));
    if (it->heap == NULL) {
        return false;
    }

    for (size_t i = 0; i < num_inputs; ++i) {
        if (inputs[i].len > 0) {
            it->heap[it->heap_size].value = inputs[i].data[inputs[i].pos];
            it->heap[it->heap_size].source_index = i;
            it->heap_size++;
            inputs[i].pos++;
        }
    }

    for (size_t i = it->heap_size / 2; i > 0; --i) {
        heap_sift_down(it->heap, it->heap_size, i - 1);
    }

    return true;
}

bool merge_iterator_next(MergeIterator *it, int *out_value) {
    if (it == NULL || out_value == NULL || it->heap_size == 0) {
        return false;
    }

    HeapNode top = it->heap[0];
    *out_value = top.value;

    size_t src_idx = top.source_index;
    Input *src = &it->inputs[src_idx];

    if (src->pos < src->len) {
        it->heap[0].value = src->data[src->pos];
        src->pos++;
        heap_sift_down(it->heap, it->heap_size, 0);
    } else {
        it->heap[0] = it->heap[it->heap_size - 1];
        it->heap_size--;
        if (it->heap_size > 0) {
            heap_sift_down(it->heap, it->heap_size, 0);
        }
    }

    return true;
}

void merge_iterator_cleanup(MergeIterator *it) {
    /* Possible weaknesses found:
     *  Assuming that condition 'it!=NULL' is not redundant
     */
    if (it != NULL && it->heap != NULL) {
        free(it->heap);
        it->heap = NULL;
    }
    /* Possible weaknesses found:
     *  Null pointer dereference
     *  Either the condition 'it!=NULL' is redundant or there is possible null pointer dereference: it. [nullPointerRedundantCheck]
     */
    it->heap_size = 0;
}

int main(void) {
    int a[] = {1, 4, 7, 10};
    int b[] = {2, 5, 8, 11};
    int c[] = {3, 6, 9, 12};

    Input inputs[] = {
        {a, 4, 0},
        {b, 4, 0},
        {c, 4, 0}
    };
    size_t num_inputs = sizeof(inputs) / sizeof(inputs[0]);

    MergeIterator it;
    if (!merge_iterator_init(&it, inputs, num_inputs)) {
        return EXIT_FAILURE;
    }

    int value;
    while (merge_iterator_next(&it, &value)) {
        printf("%d ", value);
    }
    printf("\n");

    merge_iterator_cleanup(&it);

    return EXIT_SUCCESS;
}