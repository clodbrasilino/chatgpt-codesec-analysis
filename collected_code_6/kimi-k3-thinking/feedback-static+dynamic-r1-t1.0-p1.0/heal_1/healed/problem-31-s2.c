#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int count;
    int used;
} HashEntry;

typedef struct {
    HashEntry *entries;
    size_t capacity;
    size_t size;
} HashMap;

typedef struct {
    int value;
    int count;
} HeapNode;

typedef struct {
    HeapNode *data;
    size_t size;
    size_t capacity;
} MinHeap;

static unsigned int hash_int(int key)
{
    unsigned int x = (unsigned int)key;
    x = ((x >> 16) ^ x) * 0x45d9f3bU;
    x = ((x >> 16) ^ x) * 0x45d9f3bU;
    x = (x >> 16) ^ x;
    return x;
}

static int hashmap_init(HashMap *map, size_t capacity)
{
    if (capacity < 8) {
        capacity = 8;
    }
    map->entries = calloc(capacity, sizeof(HashEntry));
    if (map->entries == NULL) {
        return -1;
    }
    map->capacity = capacity;
    map->size = 0;
    return 0;
}

static void hashmap_free(HashMap *map)
{
    free(map->entries);
    map->entries = NULL;
    map->capacity = 0;
    map->size = 0;
}

static int hashmap_resize(HashMap *map)
{
    size_t new_capacity = map->capacity * 2;
    HashEntry *new_entries = calloc(new_capacity, sizeof(HashEntry));
    size_t i;
    size_t idx;

    if (new_entries == NULL) {
        return -1;
    }
    for (i = 0; i < map->capacity; i++) {
        if (map->entries[i].used) {
            idx = (size_t)(hash_int(map->entries[i].key) % new_capacity);
            while (new_entries[idx].used) {
                idx = (idx + 1) % new_capacity;
            }
            new_entries[idx] = map->entries[i];
        }
    }
    free(map->entries);
    map->entries = new_entries;
    map->capacity = new_capacity;
    return 0;
}

static int hashmap_add(HashMap *map, int key)
{
    size_t idx;

    if ((map->size + 1) * 2 >= map->capacity) {
        if (hashmap_resize(map) != 0) {
            return -1;
        }
    }
    idx = (size_t)(hash_int(key) % map->capacity);
    while (map->entries[idx].used) {
        if (map->entries[idx].key == key) {
            map->entries[idx].count++;
            return 0;
        }
        idx = (idx + 1) % map->capacity;
    }
    map->entries[idx].used = 1;
    map->entries[idx].key = key;
    map->entries[idx].count = 1;
    map->size++;
    return 0;
}

static int minheap_init(MinHeap *heap, size_t capacity)
{
    heap->data = malloc(capacity * sizeof(HeapNode));
    if (heap->data == NULL) {
        return -1;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return 0;
}

static void minheap_free(MinHeap *heap)
{
    free(heap->data);
    heap->data = NULL;
    heap->size = 0;
    heap->capacity = 0;
}

static void heap_swap(HeapNode *a, HeapNode *b)
{
    HeapNode tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heap_sift_up(MinHeap *heap, size_t idx)
{
    while (idx > 0) {
        size_t parent = (idx - 1) / 2;
        if (heap->data[parent].count <= heap->data[idx].count) {
            break;
        }
        heap_swap(&heap->data[parent], &heap->data[idx]);
        idx = parent;
    }
}

static void heap_sift_down(MinHeap *heap, size_t idx)
{
    for (;;) {
        size_t left = idx * 2 + 1;
        size_t right = idx * 2 + 2;
        size_t smallest = idx;
        if (left < heap->size &&
            heap->data[left].count < heap->data[smallest].count) {
            smallest = left;
        }
        if (right < heap->size &&
            heap->data[right].count < heap->data[smallest].count) {
            smallest = right;
        }
        if (smallest == idx) {
            break;
        }
        heap_swap(&heap->data[idx], &heap->data[smallest]);
        idx = smallest;
    }
}

static void minheap_push(MinHeap *heap, int value, int count)
{
    size_t idx = heap->size;

    heap->data[idx].value = value;
    heap->data[idx].count = count;
    heap->size++;
    heap_sift_up(heap, idx);
}

static void minheap_replace_top(MinHeap *heap, int value, int count)
{
    heap->data[0].value = value;
    heap->data[0].count = count;
    heap_sift_down(heap, 0);
}

int *top_k_frequent(int **lists, int num_lists, const int *list_sizes,
                    int k, int *out_count)
{
    HashMap map;
    MinHeap heap;
    int *result;
    size_t heap_capacity;
    size_t i;
    size_t n;
    int li;
    int lj;

    if (out_count == NULL) {
        return NULL;
    }
    *out_count = 0;
    if (lists == NULL || list_sizes == NULL || num_lists < 0 || k <= 0) {
        return NULL;
    }
    if (hashmap_init(&map, 16) != 0) {
        return NULL;
    }
    for (li = 0; li < num_lists; li++) {
        if (lists[li] == NULL && list_sizes[li] > 0) {
            hashmap_free(&map);
            return NULL;
        }
        for (lj = 0; lj < list_sizes[li]; lj++) {
            if (hashmap_add(&map, lists[li][lj]) != 0) {
                hashmap_free(&map);
                return NULL;
            }
        }
    }
    if (map.size == 0) {
        hashmap_free(&map);
        return NULL;
    }
    heap_capacity = ((size_t)k < map.size) ? (size_t)k : map.size;
    if (minheap_init(&heap, heap_capacity) != 0) {
        hashmap_free(&map);
        return NULL;
    }
    for (i = 0; i < map.capacity; i++) {
        if (!map.entries[i].used) {
            continue;
        }
        if (heap.size < heap.capacity) {
            minheap_push(&heap, map.entries[i].key, map.entries[i].count);
        } else if (map.entries[i].count > heap.data[0].count) {
            minheap_replace_top(&heap, map.entries[i].key,
                                map.entries[i].count);
        }
    }
    hashmap_free(&map);
    result = malloc(heap.size * sizeof(int));
    if (result == NULL) {
        minheap_free(&heap);
        return NULL;
    }
    n = heap.size;
    for (i = n; i > 0; i--) {
        result[i - 1] = heap.data[0].value;
        heap.data[0] = heap.data[heap.size - 1];
        heap.size--;
        if (heap.size > 0) {
            heap_sift_down(&heap, 0);
        }
    }
    minheap_free(&heap);
    *out_count = (int)n;
    return result;
}

int main(void)
{
    int list1[] = {1, 3, 5, 7, 9};
    int list2[] = {2, 3, 5, 8, 10};
    int list3[] = {3, 5, 6, 7, 11};
    int list4[] = {1, 5, 6, 9, 12};
    int *lists[] = {list1, list2, list3, list4};
    const int list_sizes[] = {5, 5, 5, 5};
    int num_lists = 4;
    int k = 3;
    int out_count = 0;
    int *top;
    int i;

    top = top_k_frequent(lists, num_lists, list_sizes, k, &out_count);
    if (top == NULL) {
        fprintf(stderr, "top_k_frequent failed\n");
        return EXIT_FAILURE;
    }
    printf("Top %d most frequent integers (descending frequency):\n", k);
    for (i = 0; i < out_count; i++) {
        printf("%d\n", top[i]);
    }
    free(top);
    return EXIT_SUCCESS;
}