#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} Frequency;

static int find_value(const Frequency *freq, size_t n, int value, size_t *index)
{
    size_t i;

    for (i = 0; i < n; i++) {
        if (freq[i].value == value) {
            *index = i;
            return 1;
        }
    }
    return 0;
}

static Frequency *compute_frequency(const int *const *lists,
                                    const size_t *sizes,
                                    size_t num_lists,
                                    size_t *out_count)
{
    Frequency *freq = NULL;
    Frequency *tmp = NULL;
    size_t capacity = 0;
    size_t count = 0;
    size_t i;
    size_t j;
    size_t idx;

    if (lists == NULL || sizes == NULL || out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    for (i = 0; i < num_lists; i++) {
        if (lists[i] == NULL && sizes[i] > 0) {
            free(freq);
            return NULL;
        }
        for (j = 0; j < sizes[i]; j++) {
            if (find_value(freq, count, lists[i][j], &idx)) {
                freq[idx].count++;
            } else {
                if (count == capacity) {
                    size_t new_capacity = (capacity == 0) ? 8 : capacity * 2;
                    if (new_capacity < capacity) {
                        free(freq);
                        return NULL;
                    }
                    tmp = realloc(freq, new_capacity * sizeof(Frequency));
                    if (tmp == NULL) {
                        free(freq);
                        return NULL;
                    }
                    freq = tmp;
                    capacity = new_capacity;
                }
                freq[count].value = lists[i][j];
                freq[count].count = 1;
                count++;
            }
        }
    }

    *out_count = count;
    return freq;
}

int main(void)
{
    int list1[] = {1, 2, 3, 2};
    int list2[] = {4, 5, 6, 2};
    int list3[] = {7, 1, 9, 5};
    const int *lists[] = {list1, list2, list3};
    size_t sizes[] = {4, 4, 4};
    size_t num_lists = 3;
    size_t freq_count = 0;
    size_t i;
    Frequency *freq;

    freq = compute_frequency(lists, sizes, num_lists, &freq_count);
    if (freq == NULL && freq_count == 0) {
        int has_elements = 0;
        for (i = 0; i < num_lists; i++) {
            if (sizes[i] > 0) {
                has_elements = 1;
                break;
            }
        }
        if (has_elements) {
            fprintf(stderr, "Failed to compute frequencies\n");
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < freq_count; i++) {
        if (printf("%d: %zu\n", freq[i].value, freq[i].count) < 0) {
            free(freq);
            return EXIT_FAILURE;
        }
    }

    free(freq);
    return EXIT_SUCCESS;
}