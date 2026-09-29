#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *data;
    size_t length;
    size_t pos;
} SortedInput;

typedef struct {
    int value;
    size_t input_index;
} HeapEntry;

typedef struct {
    HeapEntry *heap;
    size_t size;
    size_t capacity;
    SortedInput *inputs;
    size_t num_inputs;
} MergeIterator;

static void heap_swap(HeapEntry *a, HeapEntry *b) {
    HeapEntry tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heap_sift_up(HeapEntry *heap, size_t idx) {
    while (idx > 0) {
        size_t parent = (idx - 1) / 2;
        if (heap[parent].value <= heap[idx].value) {
            break;
        }
        heap_swap(&heap[parent], &heap[idx]);
        idx = parent;
    }
}

static void heap_sift_down(HeapEntry *heap, size_t size, size_t idx) {
    for (;;) {
        size_t left = idx * 2 + 1;
        size_t right = left + 1;
        size_t smallest = idx;

        if (left < size && heap[left].value < heap[smallest].value) {
            smallest = left;
        }
        if (right < size && heap[right].value < heap[smallest].value) {
            smallest = right;
        }
        if (smallest == idx) {
            break;
        }
        heap_swap(&heap[idx], &heap[smallest]);
        idx = smallest;
    }
}

int merge_iterator_init(MergeIterator *it, const SortedInput *inputs, size_t num_inputs) {
    if (it == NULL) {
        return -1;
    }

    it->heap = NULL;
    it->inputs = NULL;
    it->size = 0;
    it->capacity = 0;
    it->num_inputs = 0;

    if (num_inputs > 0 && inputs == NULL) {
        return -1;
    }

    if (num_inputs > 0) {
        it->inputs = malloc(num_inputs * sizeof(SortedInput));
        if (it->inputs == NULL) {
            return -1;
        }

        for (size_t i = 0; i < num_inputs; i++) {
            if (inputs[i].length > 0 && inputs[i].data == NULL) {
                free(it->inputs);
                it->inputs = NULL;
                return -1;
            }
            it->inputs[i].data = inputs[i].data;
            it->inputs[i].length = inputs[i].length;
            it->inputs[i].pos = 0;
        }

        it->heap = malloc(num_inputs * sizeof(HeapEntry));
        if (it->heap == NULL) {
            free(it->inputs);
            it->inputs = NULL;
            return -1;
        }

        it->capacity = num_inputs;
        it->num_inputs = num_inputs;
    }

    for (size_t i = 0; i < it->num_inputs; i++) {
        if (it->inputs[i].pos < it->inputs[i].length) {
            HeapEntry entry;
            entry.value = it->inputs[i].data[it->inputs[i].pos];
            entry.input_index = i;
            it->inputs[i].pos++;
            it->heap[it->size] = entry;
            it->size++;
            heap_sift_up(it->heap, it->size - 1);
        }
    }

    return 0;
}

int merge_iterator_next(MergeIterator *it, int *value) {
    if (it == NULL || value == NULL) {
        return -1;
    }
    if (it->size == 0) {
        return 0;
    }
    if (it->heap == NULL || it->inputs == NULL) {
        return -1;
    }

    HeapEntry min_entry = it->heap[0];
    *value = min_entry.value;
    size_t input_idx = min_entry.input_index;

    if (it->inputs[input_idx].pos < it->inputs[input_idx].length) {
        it->heap[0].value = it->inputs[input_idx].data[it->inputs[input_idx].pos];
        it->heap[0].input_index = input_idx;
        it->inputs[input_idx].pos++;
        heap_sift_down(it->heap, it->size, 0);
    } else {
        it->size--;
        if (it->size > 0) {
            it->heap[0] = it->heap[it->size];
            heap_sift_down(it->heap, it->size, 0);
        }
    }

    return 1;
}

void merge_iterator_destroy(MergeIterator *it) {
    if (it == NULL) {
        return;
    }

    free(it->heap);
    free(it->inputs);
    it->heap = NULL;
    it->inputs = NULL;
    it->size = 0;
    it->capacity = 0;
    it->num_inputs = 0;
}

int main(void) {
    int arr1[] = {1, 4, 7};
    int arr2[] = {2, 5, 8};
    int arr3[] = {3, 6, 9};

    /* Possible weaknesses found:
     *  Variable 'inputs' can be declared as const array [constVariable]
     */
    SortedInput inputs[] = {
        {arr1, 3, 0},
        {arr2, 3, 0},
        {arr3, 3, 0}
    };

    MergeIterator iterator;
    int value;
    int status;

    if (merge_iterator_init(&iterator, inputs, 3) != 0) {
        return EXIT_FAILURE;
    }

    while ((status = merge_iterator_next(&iterator, &value)) == 1) {
        printf("%d\n", value);
    }

    merge_iterator_destroy(&iterator);

    if (status < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}