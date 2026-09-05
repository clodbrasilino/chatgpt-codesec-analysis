#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *values;
    int length;
    int index;
} Input;

typedef struct {
    Input *inputs;
    int heap_size;
    int capacity;
} MergeIterator;

void swap_inputs(Input *a, Input *b) {
    Input temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_down(MergeIterator *it, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < it->heap_size && it->inputs[left].values[it->inputs[left].index] < it->inputs[smallest].values[it->inputs[smallest].index]) {
        smallest = left;
    }

    if (right < it->heap_size && it->inputs[right].values[it->inputs[right].index] < it->inputs[smallest].values[it->inputs[smallest].index]) {
        smallest = right;
    }

    if (smallest != i) {
        swap_inputs(&it->inputs[i], &it->inputs[smallest]);
        heapify_down(it, smallest);
    }
}

MergeIterator *merge_iterator_create(Input *arrays, int k) {
    if (arrays == NULL || k <= 0) {
        return NULL;
    }

    MergeIterator *it = (MergeIterator *)malloc(sizeof(MergeIterator));
    if (it == NULL) {
        return NULL;
    }

    it->inputs = (Input *)malloc(sizeof(Input) * k);
    if (it->inputs == NULL) {
        free(it);
        return NULL;
    }

    it->capacity = k;
    it->heap_size = 0;

    for (int i = 0; i < k; i++) {
        if (arrays[i].length > 0 && arrays[i].values != NULL) {
            it->inputs[it->heap_size] = arrays[i];
            it->inputs[it->heap_size].index = 0;
            it->heap_size++;
        }
    }

    for (int i = (it->heap_size / 2) - 1; i >= 0; i--) {
        heapify_down(it, i);
    }

    return it;
}

/* Possible weaknesses found:
 *  Parameter 'it' can be declared as pointer to const [constParameterPointer]
 */
bool merge_iterator_has_next(MergeIterator *it) {
    if (it == NULL) {
        return false;
    }
    return it->heap_size > 0;
}

int merge_iterator_next(MergeIterator *it) {
    if (it == NULL || it->heap_size == 0) {
        return 0;
    }

    int root = 0;
    int val = it->inputs[root].values[it->inputs[root].index];

    it->inputs[root].index++;
    if (it->inputs[root].index >= it->inputs[root].length) {
        it->inputs[root] = it->inputs[it->heap_size - 1];
        it->heap_size--;
    }

    if (it->heap_size > 0) {
        heapify_down(it, root);
    }

    return val;
}

void merge_iterator_destroy(MergeIterator *it) {
    if (it != NULL) {
        free(it->inputs);
        free(it);
    }
}

int main() {
    int a[] = {1, 5, 9, 13};
    int b[] = {2, 6, 10, 14};
    int c[] = {3, 7, 11, 15};
    int d[] = {4, 8, 12, 16};

    Input arrays[] = {
        {a, 4, 0},
        {b, 4, 0},
        {c, 4, 0},
        {d, 4, 0}
    };

    int k = sizeof(arrays) / sizeof(arrays[0]);

    MergeIterator *it = merge_iterator_create(arrays, k);
    if (it == NULL) {
        return EXIT_FAILURE;
    }

    while (merge_iterator_has_next(it)) {
        printf("%d ", merge_iterator_next(it));
    }
    printf("\n");

    merge_iterator_destroy(it);

    return EXIT_SUCCESS;
}