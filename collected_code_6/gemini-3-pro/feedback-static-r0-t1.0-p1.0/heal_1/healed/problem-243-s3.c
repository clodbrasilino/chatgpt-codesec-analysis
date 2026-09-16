#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int value;
    int count;
    int first_index;
} OccurenceInfo;

int compare_tuples_for_counting(const void *a, const void *b) {
    const Tuple *t1 = (const Tuple *)a;
    const Tuple *t2 = (const Tuple *)b;
    return (t1->first > t2->first) - (t1->first < t2->first);
}

int compare_occurrence(const void *a, const void *b) {
    const OccurenceInfo *o1 = (const OccurenceInfo *)a;
    const OccurenceInfo *o2 = (const OccurenceInfo *)b;
    if (o1->count != o2->count) {
        return (o1->count > o2->count) - (o1->count < o2->count);
    }
    return (o1->first_index > o2->first_index) - (o1->first_index < o2->first_index);
}

void sort_tuples_by_occurrence(Tuple *arr, size_t size) {
    if (size == 0) return;

    Tuple *original = malloc(size * sizeof(Tuple));
    if (!original) exit(EXIT_FAILURE);
    for (size_t i = 0; i < size; i++) {
        original[i] = arr[i];
    }

    Tuple *sorted_arr = malloc(size * sizeof(Tuple));
    if (!sorted_arr) {
        free(original);
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < size; i++) {
        sorted_arr[i] = arr[i];
    }
    qsort(sorted_arr, size, sizeof(Tuple), compare_tuples_for_counting);

    OccurenceInfo *counts = malloc(size * sizeof(OccurenceInfo));
    if (!counts) {
        free(original);
        free(sorted_arr);
        exit(EXIT_FAILURE);
    }

    size_t unique_count = 0;
    counts[unique_count].value = sorted_arr[0].first;
    counts[unique_count].count = 1;
    counts[unique_count].first_index = 0; 
    
    for (size_t i = 1; i < size; i++) {
        if (sorted_arr[i].first == counts[unique_count].value) {
            counts[unique_count].count++;
        } else {
            unique_count++;
            counts[unique_count].value = sorted_arr[i].first;
            counts[unique_count].count = 1;
            counts[unique_count].first_index = 0; 
        }
    }
    unique_count++;

    for (size_t i = 0; i < unique_count; i++) {
        for (size_t j = 0; j < size; j++) {
            if (original[j].first == counts[i].value) {
                counts[i].first_index = j;
                break;
            }
        }
    }

    qsort(counts, unique_count, sizeof(OccurenceInfo), compare_occurrence);

    size_t idx = 0;
    for (size_t i = 0; i < unique_count; i++) {
        for (size_t j = 0; j < size; j++) {
            if (original[j].first == counts[i].value) {
                arr[idx++] = original[j];
            }
        }
    }

    free(original);
    free(sorted_arr);
    free(counts);
}

int main(void) {
    Tuple arr[] = {{4, 1}, {2, 2}, {4, 3}, {3, 4}, {2, 5}, {4, 6}, {1, 7}};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    sort_tuples_by_occurrence(arr, size);

    for (size_t i = 0; i < size; i++) {
        printf("(%d, %d) ", arr[i].first, arr[i].second);
    }
    printf("\n");

    return 0;
}