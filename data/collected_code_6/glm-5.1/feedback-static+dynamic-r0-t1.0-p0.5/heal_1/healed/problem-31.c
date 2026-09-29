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
    int current = heap->size;
    heap->size++;

    while (current > 0 && heap->data[(current - 1) / 2].count > heap->data[current].count) {
        swap_elements(&heap->data[(current - 1) / 2], &heap->data[current]);
        current = (current - 1) / 2;
    }
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

    while (1) {
        int current_val = 0;
        int has_val = 0;
        
        for (int i = 0; i < num_lists; i++) {
            if (indices[i] < list_sizes[i]) {
                if (!has_val || lists[i][indices[i]] < current_val) {
                    current_val = lists[i][indices[i]];
                    has_val = 1;
                }
            }
        }

        if (!has_val) {
            break;
        }

        int count = 0;
        for (int i = 0; i < num_lists; i++) {
            while (indices[i] < list_sizes[i] && lists[i][indices[i]] == current_val) {
                count++;
                indices[i]++;
            }
        }

        Element elem;
        elem.value = current_val;
        elem.count = count;
        push_min_heap(heap, elem);
    }

    int* result = (int*)malloc(heap->size * sizeof(int));
    if (result == NULL) {
        free(indices);
        destroy_min_heap(heap);
        return NULL;
    }

    int result_size = heap->size;
    for (int i = result_size - 1; i >= 0; i--) {
        result[i] = heap->data[0].value;
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;
        min_heapify(heap, 0);
    }

    *return_size = result_size;
    free(indices);
    destroy_min_heap(heap);
    return result;
}

int main() {
    int list1[] = {1, 3, 5, 7};
    int list2[] = {2, 3, 6, 7, 8};
    int list3[] = {1, 3, 7, 9};
    
    int* lists[] = {list1, list2, list3};
    const int list_sizes[] = {4, 5, 4};
    int num_lists = 3;
    int k = 3;
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