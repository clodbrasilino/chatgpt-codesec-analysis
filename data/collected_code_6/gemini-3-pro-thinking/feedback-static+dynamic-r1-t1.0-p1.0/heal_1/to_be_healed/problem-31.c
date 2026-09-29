#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val;
    size_t list_idx;
    size_t elem_idx;
} MergeNode;

typedef struct {
    int val;
    int freq;
} TopKNode;

typedef struct {
    MergeNode* data;
    size_t size;
    size_t capacity;
} MergeHeap;

typedef struct {
    TopKNode* data;
    size_t size;
    size_t capacity;
} TopKHeap;

MergeHeap* create_merge_heap(size_t capacity) {
    MergeHeap* h = (MergeHeap*)malloc(sizeof(MergeHeap));
    if (!h) {
        return NULL;
    }
    h->data = (MergeNode*)malloc(sizeof(MergeNode) * capacity);
    if (!h->data) {
        free(h);
        return NULL;
    }
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void destroy_merge_heap(MergeHeap* h) {
    if (h) {
        free(h->data);
        free(h);
    }
}

void swap_merge_node(MergeNode* a, MergeNode* b) {
    MergeNode tmp = *a;
    *a = *b;
    *b = tmp;
}

void merge_heap_push(MergeHeap* h, MergeNode node) {
    if (h->size == h->capacity) {
        return;
    }
    size_t i = h->size++;
    h->data[i] = node;
    while (i != 0 && h->data[(i - 1) / 2].val > h->data[i].val) {
        swap_merge_node(&h->data[i], &h->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

MergeNode merge_heap_pop(MergeHeap* h) {
    MergeNode root = h->data[0];
    h->data[0] = h->data[--h->size];
    size_t i = 0;
    while (2 * i + 1 < h->size) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t smallest = i;
        if (h->data[left].val < h->data[smallest].val) {
            smallest = left;
        }
        if (right < h->size && h->data[right].val < h->data[smallest].val) {
            smallest = right;
        }
        if (smallest != i) {
            swap_merge_node(&h->data[i], &h->data[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
    return root;
}

TopKHeap* create_topk_heap(size_t capacity) {
    TopKHeap* h = (TopKHeap*)malloc(sizeof(TopKHeap));
    if (!h) {
        return NULL;
    }
    h->data = (TopKNode*)malloc(sizeof(TopKNode) * capacity);
    if (!h->data) {
        free(h);
        return NULL;
    }
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void destroy_topk_heap(TopKHeap* h) {
    if (h) {
        free(h->data);
        free(h);
    }
}

void swap_topk_node(TopKNode* a, TopKNode* b) {
    TopKNode tmp = *a;
    *a = *b;
    *b = tmp;
}

void topk_heap_push(TopKHeap* h, TopKNode node) {
    if (h->size < h->capacity) {
        size_t i = h->size++;
        h->data[i] = node;
        while (i != 0 && h->data[(i - 1) / 2].freq > h->data[i].freq) {
            swap_topk_node(&h->data[i], &h->data[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    } else if (node.freq > h->data[0].freq) {
        h->data[0] = node;
        size_t i = 0;
        while (2 * i + 1 < h->size) {
            size_t left = 2 * i + 1;
            size_t right = 2 * i + 2;
            size_t smallest = i;
            if (h->data[left].freq < h->data[smallest].freq) {
                smallest = left;
            }
            if (right < h->size && h->data[right].freq < h->data[smallest].freq) {
                smallest = right;
            }
            if (smallest != i) {
                swap_topk_node(&h->data[i], &h->data[smallest]);
                i = smallest;
            } else {
                break;
            }
        }
    }
}

TopKNode topk_heap_pop(TopKHeap* h) {
    TopKNode root = h->data[0];
    h->data[0] = h->data[--h->size];
    size_t i = 0;
    while (2 * i + 1 < h->size) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t smallest = i;
        if (h->data[left].freq < h->data[smallest].freq) {
            smallest = left;
        }
        if (right < h->size && h->data[right].freq < h->data[smallest].freq) {
            smallest = right;
        }
        if (smallest != i) {
            swap_topk_node(&h->data[i], &h->data[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
    return root;
}

int* get_top_k_frequent(int** lists, const size_t* list_sizes, size_t num_lists, size_t k, size_t* out_k) {
    if (!out_k) {
        return NULL;
    }
    
    *out_k = 0;

    if (!lists || !list_sizes || num_lists == 0 || k == 0) {
        return NULL;
    }

    MergeHeap* mh = create_merge_heap(num_lists);
    if (!mh) {
        return NULL;
    }

    TopKHeap* th = create_topk_heap(k);
    if (!th) {
        destroy_merge_heap(mh);
        return NULL;
    }

    for (size_t i = 0; i < num_lists; i++) {
        if (lists[i] && list_sizes[i] > 0) {
            MergeNode node;
            node.val = lists[i][0];
            node.list_idx = i;
            node.elem_idx = 0;
            merge_heap_push(mh, node);
        }
    }

    if (mh->size == 0) {
        destroy_merge_heap(mh);
        destroy_topk_heap(th);
        return NULL;
    }

    int current_val = 0;
    int current_freq = 0;
    int is_first = 1;

    while (mh->size > 0) {
        MergeNode min_node = merge_heap_pop(mh);

        if (is_first) {
            current_val = min_node.val;
            current_freq = 1;
            is_first = 0;
        } else {
            if (min_node.val == current_val) {
                current_freq++;
            } else {
                TopKNode tnode;
                tnode.val = current_val;
                tnode.freq = current_freq;
                topk_heap_push(th, tnode);

                current_val = min_node.val;
                current_freq = 1;
            }
        }

        if (min_node.elem_idx + 1 < list_sizes[min_node.list_idx]) {
            MergeNode next_node;
            next_node.val = lists[min_node.list_idx][min_node.elem_idx + 1];
            next_node.list_idx = min_node.list_idx;
            next_node.elem_idx = min_node.elem_idx + 1;
            merge_heap_push(mh, next_node);
        }
    }

    if (!is_first) {
        TopKNode tnode;
        tnode.val = current_val;
        tnode.freq = current_freq;
        topk_heap_push(th, tnode);
    }

    size_t result_size = th->size;
    *out_k = result_size;
    int* result = NULL;

    if (result_size > 0) {
        result = (int*)malloc(sizeof(int) * result_size);
        if (!result) {
            *out_k = 0;
            destroy_merge_heap(mh);
            destroy_topk_heap(th);
            return NULL;
        }
        for (size_t i = result_size; i > 0; i--) {
            TopKNode max_node = topk_heap_pop(th);
            result[i - 1] = max_node.val;
        }
    }

    destroy_merge_heap(mh);
    destroy_topk_heap(th);
    
    return result;
}

int main(void) {
    int list1[] = {1, 3, 5, 7, 9, 10};
    int list2[] = {2, 3, 5, 8, 9};
    int list3[] = {3, 5, 9, 11};

    int* lists[3];
    lists[0] = list1;
    lists[1] = list2;
    lists[2] = list3;

    /* Possible weaknesses found:
     *  Variable 'list_sizes' can be declared as const array [constVariable]
     */
    size_t list_sizes[3] = {6, 5, 4};
    size_t out_k = 0;
    size_t k = 2;

    int* result = get_top_k_frequent(lists, list_sizes, 3, k, &out_k);

    if (result) {
        for (size_t i = 0; i < out_k; i++) {
            printf("%d\n", result[i]);
        }
        free(result);
    }

    return 0;
}