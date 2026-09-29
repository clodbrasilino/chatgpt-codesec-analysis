#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t frequency;
} FrequencyEntry;

typedef struct {
    int value;
    size_t list_index;
    size_t element_index;
} CursorEntry;

static void swap_cursor_entries(CursorEntry *a, CursorEntry *b)
{
    CursorEntry temporary = *a;
    *a = *b;
    *b = temporary;
}

static int cursor_is_less(const CursorEntry *a, const CursorEntry *b)
{
    if (a->value != b->value) {
        return a->value < b->value;
    }

    return a->list_index < b->list_index;
}

static void cursor_heap_push(
    CursorEntry *heap,
    size_t *heap_size,
    CursorEntry entry)
{
    size_t index = *heap_size;

    heap[index] = entry;
    ++(*heap_size);

    while (index > 0) {
        size_t parent = (index - 1U) / 2U;

        if (!cursor_is_less(&heap[index], &heap[parent])) {
            break;
        }

        swap_cursor_entries(&heap[index], &heap[parent]);
        index = parent;
    }
}

static CursorEntry cursor_heap_pop(CursorEntry *heap, size_t *heap_size)
{
    CursorEntry result = heap[0];

    --(*heap_size);

    if (*heap_size > 0) {
        size_t index = 0;

        heap[0] = heap[*heap_size];

        for (;;) {
            size_t left = index * 2U + 1U;
            size_t right = left + 1U;
            size_t smallest = index;

            if (left < *heap_size &&
                cursor_is_less(&heap[left], &heap[smallest])) {
                smallest = left;
            }

            if (right < *heap_size &&
                cursor_is_less(&heap[right], &heap[smallest])) {
                smallest = right;
            }

            if (smallest == index) {
                break;
            }

            swap_cursor_entries(&heap[index], &heap[smallest]);
            index = smallest;
        }
    }

    return result;
}

static void swap_frequency_entries(FrequencyEntry *a, FrequencyEntry *b)
{
    FrequencyEntry temporary = *a;
    *a = *b;
    *b = temporary;
}

static int frequency_entry_is_worse(
    const FrequencyEntry *a,
    const FrequencyEntry *b)
{
    if (a->frequency != b->frequency) {
        return a->frequency < b->frequency;
    }

    return a->value > b->value;
}

static int frequency_entry_is_better(
    const FrequencyEntry *a,
    const FrequencyEntry *b)
{
    if (a->frequency != b->frequency) {
        return a->frequency > b->frequency;
    }

    return a->value < b->value;
}

static void frequency_heap_push(
    FrequencyEntry *heap,
    size_t *heap_size,
    FrequencyEntry entry)
{
    size_t index = *heap_size;

    heap[index] = entry;
    ++(*heap_size);

    while (index > 0) {
        size_t parent = (index - 1U) / 2U;

        if (!frequency_entry_is_worse(&heap[index], &heap[parent])) {
            break;
        }

        swap_frequency_entries(&heap[index], &heap[parent]);
        index = parent;
    }
}

static void frequency_heap_replace_root(
    FrequencyEntry *heap,
    size_t heap_size,
    FrequencyEntry entry)
{
    size_t index = 0;

    heap[0] = entry;

    for (;;) {
        size_t left = index * 2U + 1U;
        size_t right = left + 1U;
        size_t worst = index;

        if (left < heap_size &&
            frequency_entry_is_worse(&heap[left], &heap[worst])) {
            worst = left;
        }

        if (right < heap_size &&
            frequency_entry_is_worse(&heap[right], &heap[worst])) {
            worst = right;
        }

        if (worst == index) {
            break;
        }

        swap_frequency_entries(&heap[index], &heap[worst]);
        index = worst;
    }
}

static int compare_frequency_entries(const void *left, const void *right)
{
    const FrequencyEntry *a = left;
    const FrequencyEntry *b = right;

    if (a->frequency > b->frequency) {
        return -1;
    }

    if (a->frequency < b->frequency) {
        return 1;
    }

    if (a->value < b->value) {
        return -1;
    }

    if (a->value > b->value) {
        return 1;
    }

    return 0;
}

int top_k_frequent(
    const int *const *lists,
    const size_t *lengths,
    size_t list_count,
    size_t k,
    FrequencyEntry **results,
    size_t *result_count)
{
    CursorEntry *cursor_heap = NULL;
    FrequencyEntry *frequency_heap = NULL;
    size_t cursor_heap_size = 0;
    size_t frequency_heap_size = 0;
    size_t nonempty_list_count = 0;
    size_t result_capacity = 0;
    size_t i;

    if (results == NULL || result_count == NULL) {
        return EINVAL;
    }

    *results = NULL;
    *result_count = 0;

    if (list_count > 0 && (lists == NULL || lengths == NULL)) {
        return EINVAL;
    }

    for (i = 0; i < list_count; ++i) {
        size_t j;

        if (lengths[i] > 0 && lists[i] == NULL) {
            return EINVAL;
        }

        for (j = 1; j < lengths[i]; ++j) {
            if (lists[i][j - 1U] >= lists[i][j]) {
                return EINVAL;
            }
        }

        if (lengths[i] > 0) {
            ++nonempty_list_count;
        }

        if (result_capacity < k) {
            size_t remaining = k - result_capacity;

            if (lengths[i] >= remaining) {
                result_capacity = k;
            } else {
                result_capacity += lengths[i];
            }
        }
    }

    if (k == 0 || nonempty_list_count == 0 || result_capacity == 0) {
        return 0;
    }

    if (nonempty_list_count > SIZE_MAX / sizeof(*cursor_heap) ||
        result_capacity > SIZE_MAX / sizeof(*frequency_heap)) {
        return EOVERFLOW;
    }

    cursor_heap = malloc(nonempty_list_count * sizeof(*cursor_heap));
    frequency_heap = malloc(result_capacity * sizeof(*frequency_heap));

    if (cursor_heap == NULL || frequency_heap == NULL) {
        free(cursor_heap);
        free(frequency_heap);
        return ENOMEM;
    }

    for (i = 0; i < list_count; ++i) {
        if (lengths[i] > 0) {
            CursorEntry entry;

            entry.value = lists[i][0];
            entry.list_index = i;
            entry.element_index = 0;

            cursor_heap_push(
                cursor_heap,
                &cursor_heap_size,
                entry);
        }
    }

    while (cursor_heap_size > 0) {
        int current_value = cursor_heap[0].value;
        size_t frequency = 0;
        FrequencyEntry candidate;

        while (cursor_heap_size > 0 &&
               cursor_heap[0].value == current_value) {
            CursorEntry cursor =
                cursor_heap_pop(cursor_heap, &cursor_heap_size);

            ++frequency;
            ++cursor.element_index;

            if (cursor.element_index < lengths[cursor.list_index]) {
                cursor.value =
                    lists[cursor.list_index][cursor.element_index];

                cursor_heap_push(
                    cursor_heap,
                    &cursor_heap_size,
                    cursor);
            }
        }

        candidate.value = current_value;
        candidate.frequency = frequency;

        if (frequency_heap_size < result_capacity) {
            frequency_heap_push(
                frequency_heap,
                &frequency_heap_size,
                candidate);
        } else if (frequency_entry_is_better(
                       &candidate,
                       &frequency_heap[0])) {
            frequency_heap_replace_root(
                frequency_heap,
                frequency_heap_size,
                candidate);
        }
    }

    free(cursor_heap);

    qsort(
        frequency_heap,
        frequency_heap_size,
        sizeof(*frequency_heap),
        compare_frequency_entries);

    *results = frequency_heap;
    *result_count = frequency_heap_size;

    return 0;
}

int main(void)
{
    static const int list1[] = {1, 4, 7, 10};
    static const int list2[] = {1, 2, 4, 8};
    static const int list3[] = {1, 4, 6, 8};
    static const int list4[] = {2, 4, 8, 10};
    const int *lists[] = {list1, list2, list3, list4};
    const size_t lengths[] = {
        sizeof(list1) / sizeof(list1[0]),
        sizeof(list2) / sizeof(list2[0]),
        sizeof(list3) / sizeof(list3[0]),
        sizeof(list4) / sizeof(list4[0])
    };
    FrequencyEntry *results = NULL;
    size_t result_count = 0;
    size_t i;
    int status;

    status = top_k_frequent(
        lists,
        lengths,
        sizeof(lists) / sizeof(lists[0]),
        3,
        &results,
        &result_count);

    if (status != 0) {
        fprintf(stderr, "top_k_frequent failed with error %d\n", status);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_count; ++i) {
        printf("%d %zu\n", results[i].value, results[i].frequency);
    }

    free(results);
    return EXIT_SUCCESS;
}