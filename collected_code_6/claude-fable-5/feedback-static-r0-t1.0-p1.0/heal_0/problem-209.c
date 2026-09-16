#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} MinHeap;

static MinHeap *heap_create(size_t capacity)
{
    MinHeap *h;

    if (capacity == 0) {
        return NULL;
    }

    h = malloc(sizeof(MinHeap));
    if (h == NULL) {
        return NULL;
    }

    h->data = malloc(capacity * sizeof(int));
    if (h->data == NULL) {
        free(h);
        return NULL;
    }

    h->size = 0;
    h->capacity = capacity;
    return h;
}

static void heap_destroy(MinHeap *h)
{
    if (h != NULL) {
        free(h->data);
        free(h);
    }
}

static void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void sift_down(MinHeap *h, size_t index)
{
    for (;;) {
        size_t left = 2U * index + 1U;
        size_t right = 2U * index + 2U;
        size_t smallest = index;

        if (left < h->size && h->data[left] < h->data[smallest]) {
            smallest = left;
        }
        if (right < h->size && h->data[right] < h->data[smallest]) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        swap(&h->data[index], &h->data[smallest]);
        index = smallest;
    }
}

static void sift_up(MinHeap *h, size_t index)
{
    while (index > 0U) {
        size_t parent = (index - 1U) / 2U;

        if (h->data[parent] <= h->data[index]) {
            break;
        }
        swap(&h->data[parent], &h->data[index]);
        index = parent;
    }
}

static int heap_insert(MinHeap *h, int value)
{
    if (h == NULL || h->size >= h->capacity) {
        return -1;
    }

    h->data[h->size] = value;
    h->size++;
    sift_up(h, h->size - 1U);
    return 0;
}

static int heap_delete_min_and_insert(MinHeap *h, int new_value, int *deleted)
{
    if (h == NULL || deleted == NULL || h->size == 0U) {
        return -1;
    }

    *deleted = h->data[0];
    h->data[0] = new_value;
    sift_down(h, 0U);
    return 0;
}

static void heap_print(const MinHeap *h)
{
    size_t i;

    if (h == NULL) {
        return;
    }

    for (i = 0U; i < h->size; i++) {
        printf("%d ", h->data[i]);
    }
    printf("\n");
}

int main(void)
{
    MinHeap *h;
    int initial[] = {15, 3, 17, 10, 84, 19, 6, 22, 9};
    size_t count = sizeof(initial) / sizeof(initial[0]);
    size_t i;
    int deleted;

    h = heap_create(count);
    if (h == NULL) {
        fprintf(stderr, "Failed to create heap\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        if (heap_insert(h, initial[i]) != 0) {
            fprintf(stderr, "Failed to insert element\n");
            heap_destroy(h);
            return EXIT_FAILURE;
        }
    }

    printf("Heap before: ");
    heap_print(h);

    if (heap_delete_min_and_insert(h, 12, &deleted) != 0) {
        fprintf(stderr, "Failed to replace minimum\n");
        heap_destroy(h);
        return EXIT_FAILURE;
    }

    printf("Deleted minimum: %d\n", deleted);
    printf("Heap after inserting 12: ");
    heap_print(h);

    heap_destroy(h);
    return EXIT_SUCCESS;
}