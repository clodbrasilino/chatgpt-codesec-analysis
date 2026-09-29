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

MergeIterator *merge_iterator_create(Input *inputs, int count) {
    if (inputs == NULL || count <= 0) {
        return NULL;
    }

    MergeIterator *it = (MergeIterator *)malloc(sizeof(MergeIterator));
    if (it == NULL) {
        return NULL;
    }

    it->inputs = (Input *)malloc(sizeof(Input) * count);
    if (it->inputs == NULL) {
        free(it);
        return NULL;
    }

    it->capacity = count;
    it->heap_size = 0;

    for (int i = 0; i < count; i++) {
        if (inputs[i].values != NULL && inputs[i].length > 0) {
            it->inputs[it->heap_size] = inputs[i];
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

int merge_iterator_next(MergeIterator *it, bool *success) {
    if (it == NULL || it->heap_size == 0) {
        if (success != NULL) {
            *success = false;
        }
        return 0;
    }

    int val = it->inputs[0].values[it->inputs[0].index];
    it->inputs[0].index++;

    if (it->inputs[0].index >= it->inputs[0].length) {
        it->inputs[0] = it->inputs[it->heap_size - 1];
        it->heap_size--;
    } 

    if (it->heap_size > 0) {
        heapify_down(it, 0);
    }

    if (success != NULL) {
        *success = true;
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
    int a[] = {1, 4, 7, 10};
    int b[] = {2, 5, 8, 11};
    int c[] = {3, 6, 9, 12};
    int d[] = {0};

    Input inputs[] = {
        {a, 4, 0},
        {b, 4, 0},
        {c, 4, 0},
        {d, 0, 0}
    };

    int count = sizeof(inputs) / sizeof(inputs[0]);

    MergeIterator *it = merge_iterator_create(inputs, count);
    if (it == NULL) {
        return EXIT_FAILURE;
    }

    while (merge_iterator_has_next(it)) {
        bool success = false;
        int val = merge_iterator_next(it, &success);
        if (success) {
            printf("%d ", val);
        }
    }
    printf("\n");

    merge_iterator_destroy(it);

    return EXIT_SUCCESS;
}