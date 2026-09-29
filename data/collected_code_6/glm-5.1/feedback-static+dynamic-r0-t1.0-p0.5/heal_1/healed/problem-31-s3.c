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
    if (heap == NULL) return NULL;
    heap->data = (Element*)malloc(capacity * sizeof(Element));
    if (heap->data == NULL) {
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

void min_heapify(MinHeap* heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->data[left].count < heap->data[smallest].count) {
        smallest = left;
    }

    if (right < heap->size && heap->data[right].count < heap->data[smallest].count) {
        smallest = right;
    }

    if (smallest != index) {
        swap_elements(&heap->data[index], &heap->data[smallest]);
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
    int current = heap->size;
    heap->size++;

    while (current > 0 && heap->data[(current - 1) / 2].count > heap->data[current].count) {
        swap_elements(&heap->data[(current - 1) / 2], &heap->data[current]);
        current = (current - 1) / 2;
    }
}

int* top_k_frequent(int** lists, const int* list_sizes, int num_lists, int k, int* return_size) {
    if (k <= 0 || num_lists <= 0) {
        *return_size = 0;
        return NULL;
    }

    MinHeap* heap = create_min_heap(k);
    if (heap == NULL) {
        *return_size = 0;
        return NULL;
    }

    int* indices = (int*)calloc(num_lists, sizeof(int));
    if (indices == NULL) {
        destroy_min_heap(heap);
        *return_size = 0;
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

        int count = 0;

        while (1) {
            int next_min_val = 0;
            int next_min_list = -1;
            int next_found = 0;

            for (int i = 0; i < num_lists; i++) {
                if (indices[i] < list_sizes[i]) {
                    if (!next_found || lists[i][indices[i]] < next_min_val) {
                        next_min_val = lists[i][indices[i]];
                        next_min_list = i;
                        next_found = 1;
                    }
                }
            }

            if (!next_found || next_min_val != current_value) {
                break;
            }

            count++;
            indices[next_min_list]++;
        }

        Element elem;
        elem.value = current_value;
        elem.count = count;
        push_min_heap(heap, elem);

        current_value = next_found ? next_min_val : current_value;
    }

    int result_size = heap->size;
    int* result = (int*)malloc(result_size * sizeof(int));
    if (result == NULL) {
        free(indices);
        destroy_min_heap(heap);
        *return_size = 0;
        return NULL;
    }

    for (int i = result_size - 1; i >= 0; i--) {
        result[i] = heap->data[0].value;
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;
        min_heapify(heap, 0);
    }

    free(indices);
    destroy_min_heap(heap);
    *return_size = result_size;
    return result;
}

int main() {
    int list1[] = {1, 3, 5, 7};
    int list2[] = {2, 3, 6, 7, 9};
    int list3[] = {3, 4, 7, 8};
    
    int* lists[] = {list1, list2, list3};
    const int list_sizes[] = {4, 5, 4};
    int num_lists = 3;
    int k = 2;
    int return_size = 0;

    int* result = top_k_frequent(lists, list_sizes, num_lists, k, &return_size);

    if (result != NULL) {
        for (int i = 0; i < return_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}