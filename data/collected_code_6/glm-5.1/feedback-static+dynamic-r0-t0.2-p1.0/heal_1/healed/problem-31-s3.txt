#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int frequency;
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
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

void swap_elements(Element* a, Element* b) {
    Element temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify_up(MinHeap* heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->data[index].frequency >= heap->data[parent].frequency) {
            break;
        }
        swap_elements(&heap->data[index], &heap->data[parent]);
        index = parent;
    }
}

void min_heapify_down(MinHeap* heap, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < heap->size && heap->data[left].frequency < heap->data[smallest].frequency) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right].frequency < heap->data[smallest].frequency) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        swap_elements(&heap->data[index], &heap->data[smallest]);
        index = smallest;
    }
}

void push_min_heap(MinHeap* heap, Element element) {
    if (heap->size < heap->capacity) {
        heap->data[heap->size] = element;
        heap->size++;
        min_heapify_up(heap, heap->size - 1);
    } else if (element.frequency > heap->data[0].frequency) {
        heap->data[0] = element;
        min_heapify_down(heap, 0);
    }
}

int compare_ints(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int* top_k_frequent(int** lists, const int* list_sizes, int num_lists, int k, int* return_size) {
    int total_elements = 0;
    for (int i = 0; i < num_lists; i++) {
        total_elements += list_sizes[i];
    }

    if (total_elements == 0 || k <= 0) {
        *return_size = 0;
        return NULL;
    }

    int* merged = (int*)malloc(total_elements * sizeof(int));
    if (!merged) {
        *return_size = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < num_lists; i++) {
        for (int j = 0; j < list_sizes[i]; j++) {
            merged[index++] = lists[i][j];
        }
    }

    qsort(merged, total_elements, sizeof(int), compare_ints);

    MinHeap* heap = create_min_heap(k);
    if (!heap) {
        free(merged);
        *return_size = 0;
        return NULL;
    }

    int current_val = merged[0];
    int current_freq = 1;

    for (int i = 1; i < total_elements; i++) {
        if (merged[i] == current_val) {
            current_freq++;
        } else {
            Element elem = {current_val, current_freq};
            push_min_heap(heap, elem);
            current_val = merged[i];
            current_freq = 1;
        }
    }
    Element last_elem = {current_val, current_freq};
    push_min_heap(heap, last_elem);

    free(merged);

    int result_size = heap->size;
    int* result = (int*)malloc(result_size * sizeof(int));
    if (!result) {
        destroy_min_heap(heap);
        *return_size = 0;
        return NULL;
    }

    for (int i = result_size - 1; i >= 0; i--) {
        result[i] = heap->data[0].value;
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;
        min_heapify_down(heap, 0);
    }

    destroy_min_heap(heap);
    *return_size = result_size;
    return result;
}

int main() {
    int list1[] = {1, 2, 3};
    int list2[] = {2, 3, 4, 5};
    int list3[] = {3, 5, 6};
    
    int* lists[] = {list1, list2, list3};
    const int list_sizes[] = {3, 4, 3};
    int num_lists = 3;
    int k = 2;
    int return_size = 0;

    int* result = top_k_frequent(lists, list_sizes, num_lists, k, &return_size);

    if (result) {
        for (int i = 0; i < return_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}