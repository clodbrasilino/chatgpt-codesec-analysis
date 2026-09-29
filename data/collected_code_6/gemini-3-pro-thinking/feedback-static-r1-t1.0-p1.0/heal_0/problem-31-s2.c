#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val;
    int list_idx;
    int elem_idx;
} MergeNode;

typedef struct {
    int freq;
    int val;
} TopKNode;

void sift_down_merge(MergeNode* heap, int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].val < heap[smallest].val) {
        smallest = left;
    }
    if (right < size && heap[right].val < heap[smallest].val) {
        smallest = right;
    }
    if (smallest != i) {
        MergeNode temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        sift_down_merge(heap, size, smallest);
    }
}

void sift_up_merge(MergeNode* heap, int i) {
    int parent = (i - 1) / 2;
    if (parent >= 0 && heap[i].val < heap[parent].val) {
        MergeNode temp = heap[i];
        heap[i] = heap[parent];
        heap[parent] = temp;
        sift_up_merge(heap, parent);
    }
}

void push_merge(MergeNode* heap, int* size, MergeNode node) {
    heap[*size] = node;
    (*size)++;
    sift_up_merge(heap, *size - 1);
}

MergeNode pop_merge(MergeNode* heap, int* size) {
    MergeNode root = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    sift_down_merge(heap, *size, 0);
    return root;
}

void sift_down_topk(TopKNode* heap, int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].freq < heap[smallest].freq) {
        smallest = left;
    }
    if (right < size && heap[right].freq < heap[smallest].freq) {
        smallest = right;
    }
    if (smallest != i) {
        TopKNode temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        sift_down_topk(heap, size, smallest);
    }
}

void sift_up_topk(TopKNode* heap, int i) {
    int parent = (i - 1) / 2;
    if (parent >= 0 && heap[i].freq < heap[parent].freq) {
        TopKNode temp = heap[i];
        heap[i] = heap[parent];
        heap[parent] = temp;
        sift_up_topk(heap, parent);
    }
}

void push_topk(TopKNode* heap, int* size, int k, int freq, int val) {
    if (*size < k) {
        heap[*size] = (TopKNode){freq, val};
        (*size)++;
        sift_up_topk(heap, *size - 1);
    } else if (freq > heap[0].freq) {
        heap[0] = (TopKNode){freq, val};
        sift_down_topk(heap, *size, 0);
    }
}

int* find_top_k(int** lists, const int* list_sizes, int num_lists, int k, int* out_count) {
    if (!lists || !list_sizes || num_lists <= 0 || k <= 0 || !out_count) {
        if (out_count) {
            *out_count = 0;
        }
        return NULL;
    }

    MergeNode* merge_heap = (MergeNode*)malloc(sizeof(MergeNode) * num_lists);
    if (!merge_heap) {
        *out_count = 0;
        return NULL;
    }

    int merge_size = 0;
    for (int i = 0; i < num_lists; i++) {
        if (list_sizes[i] > 0 && lists[i] != NULL) {
            push_merge(merge_heap, &merge_size, (MergeNode){lists[i][0], i, 0});
        }
    }

    if (merge_size == 0) {
        free(merge_heap);
        *out_count = 0;
        return NULL;
    }

    TopKNode* topk_heap = (TopKNode*)malloc(sizeof(TopKNode) * k);
    if (!topk_heap) {
        free(merge_heap);
        *out_count = 0;
        return NULL;
    }

    int topk_size = 0;
    MergeNode first = pop_merge(merge_heap, &merge_size);
    int current_val = first.val;
    int current_freq = 1;

    if (first.elem_idx + 1 < list_sizes[first.list_idx]) {
        push_merge(merge_heap, &merge_size, (MergeNode){lists[first.list_idx][first.elem_idx + 1], first.list_idx, first.elem_idx + 1});
    }

    while (merge_size > 0) {
        MergeNode current = pop_merge(merge_heap, &merge_size);
        if (current.val == current_val) {
            current_freq++;
        } else {
            push_topk(topk_heap, &topk_size, k, current_freq, current_val);
            current_val = current.val;
            current_freq = 1;
        }

        if (current.elem_idx + 1 < list_sizes[current.list_idx]) {
            push_merge(merge_heap, &merge_size, (MergeNode){lists[current.list_idx][current.elem_idx + 1], current.list_idx, current.elem_idx + 1});
        }
    }

    push_topk(topk_heap, &topk_size, k, current_freq, current_val);
    free(merge_heap);

    int* results = (int*)malloc(sizeof(int) * topk_size);
    if (!results) {
        free(topk_heap);
        *out_count = 0;
        return NULL;
    }

    for (int i = 0; i < topk_size; i++) {
        results[i] = topk_heap[i].val;
    }

    *out_count = topk_size;
    free(topk_heap);
    return results;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5, 9, 10};
    int list2[] = {2, 4, 6, 8, 9};
    int list3[] = {2, 3, 4, 7, 9};
    int list4[] = {4, 9, 11};

    int* lists[] = {list1, list2, list3, list4};
    int list_sizes[] = {7, 5, 5, 3};
    int num_lists = 4;
    int k = 2;
    int out_count = 0;

    int* results = find_top_k(lists, list_sizes, num_lists, k, &out_count);

    if (results) {
        for (int i = 0; i < out_count; i++) {
            printf("%d\n", results[i]);
        }
        free(results);
    }

    return 0;
}