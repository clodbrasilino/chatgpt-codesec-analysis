#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *data;
    size_t length;
    size_t position;
} SortedInput;

typedef struct {
    SortedInput *inputs;
    size_t input_count;
    size_t *heap;
    size_t heap_size;
} MergeIterator;

static void merge_iter_swap(size_t *a, size_t *b) {
    size_t tmp = *a;
    *a = *b;
    *b = tmp;
}

static int merge_iter_less(const MergeIterator *it, size_t left, size_t right) {
    const SortedInput *a = &it->inputs[left];
    const SortedInput *b = &it->inputs[right];
    return a->data[a->position] < b->data[b->position];
}

static void merge_iter_sift_down(MergeIterator *it, size_t index) {
    size_t size = it->heap_size;
    while (index < size) {
        size_t left = index * 2 + 1;
        size_t right = left + 1;
        size_t smallest = index;
        if (left < size && merge_iter_less(it, it->heap[left], it->heap[smallest])) {
            smallest = left;
        }
        if (right < size && merge_iter_less(it, it->heap[right], it->heap[smallest])) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        merge_iter_swap(&it->heap[index], &it->heap[smallest]);
        index = smallest;
    }
}

MergeIterator *merge_iter_create(SortedInput *inputs, size_t count) {
    if (!inputs && count > 0) {
        return NULL;
    }
    MergeIterator *it = malloc(sizeof(*it));
    if (!it) {
        return NULL;
    }
    it->inputs = inputs;
    it->input_count = count;
    it->heap_size = 0;
    it->heap = NULL;
    if (count > 0) {
        it->heap = malloc(count * sizeof(*it->heap));
        if (!it->heap) {
            free(it);
            return NULL;
        }
    }
    for (size_t i = 0; i < count; ++i) {
        if (inputs[i].position < inputs[i].length) {
            it->heap[it->heap_size++] = i;
        }
    }
    for (size_t i = it->heap_size / 2; i > 0; --i) {
        merge_iter_sift_down(it, i - 1);
    }
    return it;
}

void merge_iter_destroy(MergeIterator *it) {
    if (!it) {
        return;
    }
    free(it->heap);
    free(it);
}

int merge_iter_next(MergeIterator *it, int *value) {
    if (!it || !value || it->heap_size == 0) {
        return 0;
    }
    size_t input_index = it->heap[0];
    SortedInput *input = &it->inputs[input_index];
    *value = input->data[input->position++];
    if (input->position >= input->length) {
        if (it->heap_size > 1) {
            it->heap[0] = it->heap[--it->heap_size];
        } else {
            it->heap_size = 0;
        }
    }
    if (it->heap_size > 0) {
        merge_iter_sift_down(it, 0);
    }
    return 1;
}

int main(void) {
    int a[] = {1, 4, 7};
    int b[] = {2, 5, 8, 11};
    int c[] = {3, 6, 9, 10};
    SortedInput inputs[] = {
        {a, sizeof(a) / sizeof(a[0]), 0},
        {b, sizeof(b) / sizeof(b[0]), 0},
        {c, sizeof(c) / sizeof(c[0]), 0}
    };
    MergeIterator *it = merge_iter_create(inputs, 3);
    if (!it) {
        fprintf(stderr, "failed to create iterator\n");
        return 1;
    }
    int value;
    while (merge_iter_next(it, &value)) {
        printf("%d\n", value);
    }
    merge_iter_destroy(it);
    return 0;
}