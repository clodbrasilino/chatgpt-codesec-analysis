#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void sift_down(int *heap, size_t start, size_t end)
{
    size_t root = start;

    while (root * 2 + 1 <= end) {
        size_t child = root * 2 + 1;

        if (child + 1 <= end && heap[child + 1] < heap[child]) {
            child = child + 1;
        }

        if (heap[root] > heap[child]) {
            int tmp = heap[root];
            heap[root] = heap[child];
            heap[child] = tmp;
            root = child;
        } else {
            return;
        }
    }
}

static void heapify(int *heap, size_t count)
{
    if (count < 2) {
        return;
    }

    size_t start = (count - 2) / 2;

    for (;;) {
        sift_down(heap, start, count - 1);
        if (start == 0) {
            break;
        }
        start--;
    }
}

static int compare_desc(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return 1;
    }
    if (x > y) {
        return -1;
    }
    return 0;
}

int *find_largest(const int *numbers, size_t count, size_t k, size_t *result_count)
{
    if (numbers == NULL || result_count == NULL || k == 0 || count == 0) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    if (k > count) {
        k = count;
    }

    int *heap = malloc(k * sizeof(int));
    if (heap == NULL) {
        *result_count = 0;
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(heap, numbers, k * sizeof(int));
    heapify(heap, k);

    for (size_t i = k; i < count; i++) {
        if (numbers[i] > heap[0]) {
            heap[0] = numbers[i];
            sift_down(heap, 0, k - 1);
        }
    }

    qsort(heap, k, sizeof(int), compare_desc);
    *result_count = k;
    return heap;
}

int main(void)
{
    int numbers[] = {25, 35, 22, 85, 14, 65, 75, 22, 58};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    size_t result_count = 0;

    int *largest = find_largest(numbers, count, 3, &result_count);
    if (largest == NULL) {
        fprintf(stderr, "Failed to find largest numbers\n");
        return EXIT_FAILURE;
    }

    printf("The %zu largest numbers are:", result_count);
    for (size_t i = 0; i < result_count; i++) {
        printf(" %d", largest[i]);
    }
    printf("\n");

    free(largest);
    return EXIT_SUCCESS;
}