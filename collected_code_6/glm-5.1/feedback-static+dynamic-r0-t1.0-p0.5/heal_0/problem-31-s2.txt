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
    heap->data = (Element*)malloc(capacity * sizeof(Element));
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
    heap->size++;
    int i = heap->size - 1;

    while (i != 0 && heap->data[(i - 1) / 2].count > heap->data[i].count) {
        swap_elements(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int* top_k_frequent(int** lists, int* list_sizes, int num_lists, int k, int* return_size) {
    int total_elements = 0;
    for (int i = 0; i < num_lists; i++) {
        total_elements += list_sizes[i];
    }

    if (total_elements == 0 || k <= 0) {
        *return_size = 0;
        return NULL;
    }

    int* merged = (int*)malloc(total_elements * sizeof(int));
    if (merged == NULL) {
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
    if (heap == NULL) {
        free(merged);
        *return_size = 0;
        return NULL;
    }

    int current_count = 1;
    for (int i = 1; i <= total_elements; i++) {
        if (i < total_elements && merged[i] == merged[i - 1]) {
            current_count++;
        } else {
            Element elem;
            elem.value = merged[i - 1];
            elem.count = current_count;
            push_min_heap(heap, elem);
            current_count = 1;
        }
    }

    int actual_k = heap->size;
    int* result = (int*)malloc(actual_k * sizeof(int));
    if (result == NULL) {
        destroy_min_heap(heap);
        free(merged);
        *return_size = 0;
        return NULL;
    }

    for (int i = actual_k - 1; i >= 0; i--) {
        result[i] = heap->data[0].value;
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;
        min_heapify(heap, 0);
    }

    free(merged);
    destroy_min_heap(heap);
    *return_size = actual_k;
    return result;
}

int main() {
    int list1[] = {1, 2, 3};
    int list2[] = {2, 3, 4, 5};
    int list3[] = {3, 5, 6};

    int* lists[] = {list1, list2, list3};
    int list_sizes[] = {3, 4, 3};
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