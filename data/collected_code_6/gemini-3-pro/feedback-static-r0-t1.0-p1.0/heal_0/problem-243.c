#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int value;
    int count;
} ElementOccurence;

int compare_occurrences(const void *a, const void *b) {
    const ElementOccurence *occ_a = (const ElementOccurence *)a;
    const ElementOccurence *occ_b = (const ElementOccurence *)b;
    
    if (occ_a->count != occ_b->count) {
        return occ_a->count - occ_b->count;
    }
    return occ_a->value - occ_b->value;
}

int count_occurrences(Tuple *arr, int n, int value) {
    int count = 0;
    if (arr == NULL || n <= 0) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (arr[i].first == value) {
            count++;
        }
    }
    return count;
}

int sort_tuples_by_occurrence(Tuple *arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    ElementOccurence *occurrences = (ElementOccurence *)malloc(n * sizeof(ElementOccurence));
    if (occurrences == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        occurrences[i].value = arr[i].first;
        occurrences[i].count = count_occurrences(arr, n, arr[i].first);
    }

    Tuple *temp_arr = (Tuple *)malloc(n * sizeof(Tuple));
    if (temp_arr == NULL) {
        free(occurrences);
        return -1;
    }

    qsort(occurrences, n, sizeof(ElementOccurence), compare_occurrences);

    int *used = (int *)calloc(n, sizeof(int));
    if (used == NULL) {
        free(occurrences);
        free(temp_arr);
        return -1;
    }

    int idx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!used[j] && arr[j].first == occurrences[i].value) {
                temp_arr[idx++] = arr[j];
                used[j] = 1;
                break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        arr[i] = temp_arr[i];
    }

    free(used);
    free(temp_arr);
    free(occurrences);
    return 0;
}

int main(void) {
    Tuple arr[] = {{4, 1}, {2, 2}, {4, 3}, {3, 4}, {2, 5}, {4, 6}, {1, 7}};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (sort_tuples_by_occurrence(arr, n) == 0) {
        for (int i = 0; i < n; i++) {
            printf("(%d, %d) ", arr[i].first, arr[i].second);
        }
        printf("\n");
    } else {
        printf("Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}