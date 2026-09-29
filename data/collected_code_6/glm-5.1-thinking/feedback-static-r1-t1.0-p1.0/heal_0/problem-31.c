#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *arr;
    int size;
} List;

typedef struct {
    int val;
    int list_idx;
} MergeNode;

typedef struct {
    int freq;
    int val;
} FreqNode;

void merge_swap(MergeNode *a, MergeNode *b) {
    MergeNode t = *a;
    *a = *b;
    *b = t;
}

void merge_heapify_up(MergeNode *h, int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h[p].val > h[i].val) {
            merge_swap(&h[p], &h[i]);
            i = p;
        } else {
            break;
        }
    }
}

void merge_heapify_down(MergeNode *h, int n, int i) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && h[l].val < h[smallest].val) smallest = l;
    if (r < n && h[r].val < h[smallest].val) smallest = r;
    if (smallest != i) {
        merge_swap(&h[i], &h[smallest]);
        merge_heapify_down(h, n, smallest);
    }
}

void merge_push(MergeNode *h, int *n, MergeNode item) {
    h[*n] = item;
    merge_heapify_up(h, *n);
    (*n)++;
}

MergeNode merge_pop(MergeNode *h, int *n) {
    MergeNode root = h[0];
    (*n)--;
    h[0] = h[*n];
    merge_heapify_down(h, *n, 0);
    return root;
}

void freq_swap(FreqNode *a, FreqNode *b) {
    FreqNode t = *a;
    *a = *b;
    *b = t;
}

void freq_heapify_up(FreqNode *h, int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h[p].freq > h[i].freq) {
            freq_swap(&h[p], &h[i]);
            i = p;
        } else {
            break;
        }
    }
}

void freq_heapify_down(FreqNode *h, int n, int i) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && h[l].freq < h[smallest].freq) smallest = l;
    if (r < n && h[r].freq < h[smallest].freq) smallest = r;
    if (smallest != i) {
        freq_swap(&h[i], &h[smallest]);
        freq_heapify_down(h, n, smallest);
    }
}

void freq_push(FreqNode *h, int *n, FreqNode item) {
    h[*n] = item;
    freq_heapify_up(h, *n);
    (*n)++;
}

FreqNode freq_pop(FreqNode *h, int *n) {
    FreqNode root = h[0];
    (*n)--;
    h[0] = h[*n];
    freq_heapify_down(h, *n, 0);
    return root;
}

int* findTopKFrequent(List* lists, int num_lists, int k, int* result_size) {
    *result_size = 0;
    if (k <= 0) return NULL;

    int total_elements = 0;
    for (int i = 0; i < num_lists; i++) {
        total_elements += lists[i].size;
    }
    if (total_elements == 0) return NULL;

    MergeNode* merge_heap = (MergeNode*)malloc(num_lists * sizeof(MergeNode));
    if (!merge_heap) return NULL;

    int* current_indices = (int*)calloc(num_lists, sizeof(int));
    if (!current_indices) {
        free(merge_heap);
        return NULL;
    }

    int merge_size = 0;
    for (int i = 0; i < num_lists; i++) {
        if (lists[i].size > 0) {
            MergeNode item;
            item.val = lists[i].arr[current_indices[i]];
            item.list_idx = i;
            merge_push(merge_heap, &merge_size, item);
        }
    }

    int freq_heap_cap = k;
    FreqNode* freq_heap = (FreqNode*)malloc(freq_heap_cap * sizeof(FreqNode));
    if (!freq_heap) {
        free(merge_heap);
        free(current_indices);
        return NULL;
    }
    int freq_size = 0;

    int prev_val = INT_MIN;
    int curr_freq = 0;
    int first = 1;

    while (merge_size > 0) {
        MergeNode top = merge_pop(merge_heap, &merge_size);

        if (first || top.val != prev_val) {
            if (!first) {
                if (freq_size < k) {
                    FreqNode fn;
                    fn.freq = curr_freq;
                    fn.val = prev_val;
                    freq_push(freq_heap, &freq_size, fn);
                } else if (curr_freq > freq_heap[0].freq) {
                    freq_pop(freq_heap, &freq_size);
                    FreqNode fn;
                    fn.freq = curr_freq;
                    fn.val = prev_val;
                    freq_push(freq_heap, &freq_size, fn);
                }
            }
            prev_val = top.val;
            curr_freq = 1;
            first = 0;
        } else {
            curr_freq++;
        }

        int list_idx = top.list_idx;
        current_indices[list_idx]++;
        if (current_indices[list_idx] < lists[list_idx].size) {
            MergeNode next_item;
            next_item.val = lists[list_idx].arr[current_indices[list_idx]];
            next_item.list_idx = list_idx;
            merge_push(merge_heap, &merge_size, next_item);
        }
    }

    if (!first) {
        if (freq_size < k) {
            FreqNode fn;
            fn.freq = curr_freq;
            fn.val = prev_val;
            freq_push(freq_heap, &freq_size, fn);
        } else if (curr_freq > freq_heap[0].freq) {
            freq_pop(freq_heap, &freq_size);
            FreqNode fn;
            fn.freq = curr_freq;
            fn.val = prev_val;
            freq_push(freq_heap, &freq_size, fn);
        }
    }

    int* result = (int*)malloc(freq_size * sizeof(int));
    if (!result) {
        free(merge_heap);
        free(current_indices);
        free(freq_heap);
        return NULL;
    }

    *result_size = freq_size;
    for (int i = freq_size - 1; i >= 0; i--) {
        FreqNode fn = freq_pop(freq_heap, &freq_size);
        result[i] = fn.val;
    }

    free(merge_heap);
    free(current_indices);
    free(freq_heap);
    
    return result;
}

int main() {
    int arr0[] = {1, 4, 7};
    int arr1[] = {1, 2, 4, 6};
    int arr2[] = {4, 5, 6};
    
    List lists[3];
    lists[0].arr = arr0;
    lists[0].size = 3;
    lists[1].arr = arr1;
    lists[1].size = 4;
    lists[2].arr = arr2;
    lists[2].size = 3;

    int k = 2;
    int result_size = 0;
    int* result = findTopKFrequent(lists, 3, k, &result_size);

    if (result) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}