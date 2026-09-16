#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

typedef struct {
    IntList *list;
    size_t frequency;
} ListFrequency;

int compare_lists(const IntList *a, const IntList *b) {
    if (a->size != b->size) {
        return 0;
    }
    if (a->size == 0) {
        return 1;
    }
    return memcmp(a->data, b->data, a->size * sizeof(int)) == 0;
}

ListFrequency *count_list_frequencies(IntList *lists, size_t num_lists, size_t *result_count) {
    if (lists == NULL || result_count == NULL || num_lists == 0) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    ListFrequency *frequencies = malloc(num_lists * sizeof(ListFrequency));
    if (frequencies == NULL) {
        *result_count = 0;
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < num_lists; i++) {
        int found = 0;
        for (size_t j = 0; j < unique_count; j++) {
            if (compare_lists(&lists[i], frequencies[j].list)) {
                frequencies[j].frequency++;
                found = 1;
                break;
            }
        }
        if (!found) {
            frequencies[unique_count].list = &lists[i];
            frequencies[unique_count].frequency = 1;
            unique_count++;
        }
    }

    ListFrequency *result = realloc(frequencies, unique_count * sizeof(ListFrequency));
    if (result == NULL) {
        *result_count = unique_count;
        return frequencies;
    }

    *result_count = unique_count;
    return result;
}

void free_frequencies(ListFrequency *frequencies) {
    free(frequencies);
}

int main(void) {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5};
    int data3[] = {1, 2, 3};
    int data4[] = {6, 7, 8, 9};
    int data5[] = {4, 5};
    int data6[] = {1, 2, 3};

    IntList lists[] = {
        {data1, 3},
        {data2, 2},
        {data3, 3},
        {data4, 4},
        {data5, 2},
        {data6, 3}
    };

    size_t num_lists = sizeof(lists) / sizeof(lists[0]);
    size_t result_count = 0;

    ListFrequency *frequencies = count_list_frequencies(lists, num_lists, &result_count);

    if (frequencies == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory\n");
        return EXIT_FAILURE;
    }

    printf("Frequency count of lists:\n");
    for (size_t i = 0; i < result_count; i++) {
        printf("List [");
        for (size_t j = 0; j < frequencies[i].list->size; j++) {
            printf("%d", frequencies[i].list->data[j]);
            if (j < frequencies[i].list->size - 1) {
                printf(", ");
            }
        }
        printf("] appears %zu time(s)\n", frequencies[i].frequency);
    }

    free_frequencies(frequencies);

    return EXIT_SUCCESS;
}