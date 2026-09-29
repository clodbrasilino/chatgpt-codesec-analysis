#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef struct {
    int val;
    int freq;
} Element;

static int compare_ints(const void* a, const void* b) {
    int int_a = *((const int*)a);
    int int_b = *((const int*)b);
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

static void swap(Element* a, Element* b) {
    Element temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_down(Element* heap, int size, int index) {
    while (1) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left].freq < heap[smallest].freq) {
            smallest = left;
        }
        if (right < size && heap[right].freq < heap[smallest].freq) {
            smallest = right;
        }
        if (smallest != index) {
            swap(&heap[index], &heap[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

static void heapify_up(Element* heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].freq < heap[parent].freq) {
            swap(&heap[index], &heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

int* get_top_k(int** lists, const int* sizes, int num_lists, int k, int* out_size) {
    if (!lists || !sizes || num_lists <= 0 || k <= 0 || !out_size) {
        if (out_size) {
            *out_size = 0;
        }
        return NULL;
    }

    int total_elements = 0;
    for (int i = 0; i < num_lists; i++) {
        if (sizes[i] < 0) {
            *out_size = 0;
            return NULL;
        }
        if (sizes[i] > 0 && total_elements > INT_MAX - sizes[i]) {
            *out_size = 0;
            return NULL;
        }
        total_elements += sizes[i];
    }

    if (total_elements == 0) {
        *out_size = 0;
        return NULL;
    }

    if ((size_t)total_elements > SIZE_MAX / sizeof(int)) {
        *out_size = 0;
        return NULL;
    }

    if ((size_t)k > SIZE_MAX / sizeof(Element)) {
        *out_size = 0;
        return NULL;
    }

    int* all_elements = (int*)malloc(total_elements * sizeof(int));
    if (!all_elements) {
        *out_size = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < num_lists; i++) {
        if (lists[i] && sizes[i] > 0) {
            if (index <= total_elements - sizes[i]) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(&all_elements[index], lists[i], (size_t)sizes[i] * sizeof(int));
                index += sizes[i];
            }
        }
    }

    qsort(all_elements, total_elements, sizeof(int), compare_ints);

    Element* min_heap = (Element*)malloc(k * sizeof(Element));
    if (!min_heap) {
        free(all_elements);
        *out_size = 0;
        return NULL;
    }

    int heap_size = 0;
    int current_val = all_elements[0];
    int current_freq = 1;

    for (int i = 1; i <= total_elements; i++) {
        if (i < total_elements && all_elements[i] == current_val) {
            current_freq++;
        } else {
            if (heap_size < k) {
                min_heap[heap_size].val = current_val;
                min_heap[heap_size].freq = current_freq;
                heapify_up(min_heap, heap_size);
                heap_size++;
            } else if (current_freq > min_heap[0].freq) {
                min_heap[0].val = current_val;
                min_heap[0].freq = current_freq;
                heapify_down(min_heap, heap_size, 0);
            }

            if (i < total_elements) {
                current_val = all_elements[i];
                current_freq = 1;
            }
        }
    }

    free(all_elements);

    if (heap_size == 0) {
        free(min_heap);
        *out_size = 0;
        return NULL;
    }

    int* result = (int*)malloc(heap_size * sizeof(int));
    if (!result) {
        free(min_heap);
        *out_size = 0;
        return NULL;
    }

    for (int i = 0; i < heap_size; i++) {
        result[i] = min_heap[i].val;
    }

    *out_size = heap_size;
    free(min_heap);
    return result;
}

int main(void) {
    int list1[] = {1, 2, 3, 5, 8};
    int list2[] = {2, 3, 5, 9};
    int list3[] = {1, 2, 5, 10};

    int* lists[] = {list1, list2, list3};
    /* Possible weaknesses found:
     *  Variable 'sizes' can be declared as const array [constVariable]
     */
    int sizes[] = {5, 4, 4};
    int num_lists = 3;
    int k = 2;
    int out_size = 0;

    int* top_k = get_top_k(lists, sizes, num_lists, k, &out_size);

    if (top_k) {
        for (int i = 0; i < out_size; i++) {
            printf("%d\n", top_k[i]);
        }
        free(top_k);
    }

    return 0;
}