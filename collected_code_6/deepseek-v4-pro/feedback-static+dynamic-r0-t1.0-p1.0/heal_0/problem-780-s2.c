#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    int *indices;
    int size;
} Combination;

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int is_valid_combination(int *indices, int size, int *used, int used_size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < used_size; j++) {
            if (indices[i] == used[j]) return 0;
        }
    }
    return 1;
}

void find_combinations_recursive(Tuple *tuples, int tuple_count, int target_sum,
                                  int *current_indices, int current_size,
                                  int *used_indices, int used_count,
                                  Combination *results, int *result_count,
                                  int max_results) {
    if (target_sum == 0 && current_size > 0) {
        if (*result_count < max_results) {
            results[*result_count].indices = (int *)malloc(current_size * sizeof(int));
            if (results[*result_count].indices == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            memcpy(results[*result_count].indices, current_indices, current_size * sizeof(int));
            results[*result_count].size = current_size;
            (*result_count)++;
        }
        return;
    }

    if (target_sum < 0 || current_size >= tuple_count) {
        return;
    }

    for (int i = 0; i < tuple_count; i++) {
        if (!is_valid_combination(&i, 1, used_indices, used_count)) {
            continue;
        }

        int new_used_indices[tuple_count];
        memcpy(new_used_indices, used_indices, used_count * sizeof(int));
        new_used_indices[used_count] = i;

        int new_current_indices[tuple_count];
        memcpy(new_current_indices, current_indices, current_size * sizeof(int));
        new_current_indices[current_size] = i;

        find_combinations_recursive(tuples, tuple_count, target_sum - tuples[i].size,
                                      new_current_indices, current_size + 1,
                                      new_used_indices, used_count + 1,
                                      results, result_count, max_results);
    }
}

Combination *find_combinations(Tuple *tuples, int tuple_count, int target_sum, int *result_count) {
    if (tuples == NULL || tuple_count <= 0 || target_sum <= 0) {
        *result_count = 0;
        return NULL;
    }

    int max_possible = 1;
    for (int i = 0; i < tuple_count; i++) {
        max_possible *= 2;
    }
    if (max_possible <= 0) max_possible = 1000;

    Combination *results = (Combination *)malloc(max_possible * sizeof(Combination));
    if (results == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        *result_count = 0;
        return NULL;
    }

    int *current_indices = (int *)malloc(tuple_count * sizeof(int));
    int *used_indices = (int *)malloc(tuple_count * sizeof(int));
    if (current_indices == NULL || used_indices == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(results);
        free(current_indices);
        free(used_indices);
        *result_count = 0;
        return NULL;
    }

    *result_count = 0;
    find_combinations_recursive(tuples, tuple_count, target_sum,
                                  current_indices, 0,
                                  used_indices, 0,
                                  results, result_count, max_possible);

    free(current_indices);
    free(used_indices);

    if (*result_count == 0) {
        free(results);
        return NULL;
    }

    Combination *final_results = (Combination *)realloc(results, *result_count * sizeof(Combination));
    if (final_results == NULL && *result_count > 0) {
        fprintf(stderr, "Memory reallocation failed\n");
        for (int i = 0; i < *result_count; i++) {
            free(results[i].indices);
        }
        free(results);
        *result_count = 0;
        return NULL;
    }

    return final_results != NULL ? final_results : results;
}

void free_combinations(Combination *combinations, int count) {
    if (combinations == NULL) return;
    for (int i = 0; i < count; i++) {
        free(combinations[i].indices);
    }
    free(combinations);
}

int main(void) {
    Tuple tuples[] = {
        {(int[]){2, 3}, 2},
        {(int[]){4, 5}, 2},
        {(int[]){1}, 1},
        {(int[]){3}, 1}
    };
    int tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    int target_sum = 5;
    int result_count = 0;

    Combination *results = find_combinations(tuples, tuple_count, target_sum, &result_count);

    if (results != NULL) {
        printf("Found %d combinations of tuple sizes summing to %d:\n", result_count, target_sum);
        for (int i = 0; i < result_count; i++) {
            printf("Combination %d: ", i + 1);
            for (int j = 0; j < results[i].size; j++) {
                printf("Tuple[%d] (size %d) ", results[i].indices[j], tuples[results[i].indices[j]].size);
            }
            printf("\n");
        }
        free_combinations(results, result_count);
    } else {
        printf("No combinations found or invalid input.\n");
    }

    return 0;
}