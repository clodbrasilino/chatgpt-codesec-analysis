#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Element;

typedef struct {
    Element *data;
    int capacity;
    int size;
} MinHeap;

MinHeap* create_min_heap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    heap->data = (Element*)malloc(capacity * sizeof(Element));
    if (!heap->data) {
        free(heap);
        return NULL;
    }
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void destroy_min_heap(MinHeap* heap) {
    if (heap != NULL) {
        free(heap->data);
        free(heap);
    }
}

void swap_elements(Element* a, Element* b) {
    Element temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->data[left].count < heap->data[smallest].count) {
        smallest = left;
    }

    if (right < heap->size && heap->data[right].count < heap->data[smallest].count) {
        smallest = right;
    }

    if (smallest != idx) {
        swap_elements(&heap->data[idx], &heap->data[smallest]);
        min_heapify(heap, smallest);
    }
}

void push_min_heap(MinHeap* heap, Element element) {
    if (heap->size == heap->capacity) {
        if (element.count > heap->data[0].count) {
            heap->data[0] = element;
            min_heapify(heap, 0);
        }
        return;
    }

    heap->data[heap->size] = element;
    int i = heap->size;
    heap->size++;

    while (i != 0 && heap->data[(i - 1) / 2].count > heap->data[i].count) {
        swap_elements(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int compare_elements(const void* a, const void* b) {
    const Element* elemA = (const Element*)a;
    const Element* elemB = (const Element*)b;
    if (elemB->count != elemA->count) {
        return elemB->count - elemA->count;
    }
    return elemA->value - elemB->value;
}

int* top_k_frequent(int** lists, const int* list_sizes, int num_lists, int k, int* return_size) {
    *return_size = 0;
    
    if (k <= 0) {
        return NULL;
    }

    MinHeap* heap = create_min_heap(k);
    if (heap == NULL) {
        return NULL;
    }

    int* indices = (int*)calloc(num_lists, sizeof(int));
    if (indices == NULL) {
        destroy_min_heap(heap);
        return NULL;
    }

    int current_value = 0;
    int initialized = 0;

    while (1) {
        int min_val = 0;
        int found = 0;

        for (int i = 0; i < num_lists; i++) {
            if (indices[i] < list_sizes[i]) {
                if (!found || lists[i][indices[i]] < min_val) {
                    min_val = lists[i][indices[i]];
                    found = 1;
                }
            }
        }

        if (!found) {
            break;
        }

        if (!initialized) {
            current_value = min_val;
            initialized = 1;
        }

        if (min_val == current_value) {
            int count = 0;
            for (int i = 0; i < num_lists; i++) {
                while (indices[i] < list_sizes[i] && lists[i][indices[i]] == current_value) {
                    count++;
                    indices[i]++;
                }
            }

            Element elem;
            elem.value = current_value;
            elem.count = count;
            push_min_heap(heap, elem);

            found = 0;
            for (int i = 0; i < num_lists; i++) {
                if (indices[i] < list_sizes[i]) {
                    if (!found || lists[i][indices[i]] < min_val) {
                        min_val = lists[i][indices[i]];
                        found = 1;
                    }
                }
            }

            if (found) {
                current_value = min_val;
            }
        }
    }

    free(indices);

    if (heap->size == 0) {
        destroy_min_heap(heap);
        return NULL;
    }

    qsort(heap->data, heap->size, sizeof(Element), compare_elements);

    int result_size = heap->size;
    int* result = (int*)malloc(result_size * sizeof(int));
    if (result == NULL) {
        destroy_min_heap(heap);
        return NULL;
    }

    for (int i = 0; i < result_size; i++) {
        result[i] = heap->data[i].value;
    }

    destroy_min_heap(heap);
    *return_size = result_size;
    return result;
}

int main() {
    int list1[] = {1, 3, 5, 7};
    int list2[] = {2, 3, 6, 7, 8};
    int list3[] = {3, 4, 7, 9};
    
    int* lists[] = {list1, list2, list3};
    const int list_sizes[] = {4, 5, 4};
    int num_lists = 3;
    int k = 2;

    int return_size = 0;
    int* result = top_k_frequent(lists, list_sizes, num_lists, k, &return_size);

    if (result != NULL && return_size > 0) {
        for (int i = 0; i < return_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}