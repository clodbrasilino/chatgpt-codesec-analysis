#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
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

int is_valid_combination(const int *indices, int size, const int *used, int used_size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < used_size; j++) {
            if (indices[i] == used[j]) return 0;
        }
    }
    return 1;
}

static int safe_memcpy(void *dest, size_t dest_size, const void *src, size_t src_size) {
    if (dest == NULL || src == NULL) return 0;
    if (src_size > dest_size) return 0;
    memcpy(dest, src, src_size);
    return 1;
}

void find_combinations_recursive(const Tuple *tuples, int tuple_count, int target_sum,
                                  const int *current_indices, int current_size,
                                  const int *used_indices, int used_count,
                                  Combination *results, int *result_count,
                                  int max_results) {
    if (target_sum == 0 && current_size > 0) {
        if (*result_count < max_results) {
            size_t alloc_size = (size_t)current_size * sizeof(int);
            if (alloc_size / sizeof(int) != (size_t)current_size) return;
            results[*result_count].indices = (int *)malloc(alloc_size);
            if (results[*result_count].indices == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            if (current_indices != NULL) {
                if (!safe_memcpy(results[*result_count].indices, alloc_size, 
                                 current_indices, alloc_size)) {
                    free(results[*result_count].indices);
                    results[*result_count].indices = NULL;
                    return;
                }
            }
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

        if (used_count + 1 > tuple_count || current_size + 1 > tuple_count) {
            continue;
        }

        int new_used_size = used_count + 1;
        size_t new_used_alloc = (size_t)new_used_size * sizeof(int);
        if (new_used_alloc / sizeof(int) != (size_t)new_used_size) continue;
        int *new_used_indices = (int *)malloc(new_used_alloc);
        if (new_used_indices == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        if (used_count > 0 && used_indices != NULL) {
            if (!safe_memcpy(new_used_indices, new_used_alloc, 
                             used_indices, (size_t)used_count * sizeof(int))) {
                free(new_used_indices);
                continue;
            }
        }
        new_used_indices[used_count] = i;

        int new_current_size = current_size + 1;
        size_t new_current_alloc = (size_t)new_current_size * sizeof(int);
        if (new_current_alloc / sizeof(int) != (size_t)new_current_size) {
            free(new_used_indices);
            continue;
        }
        int *new_current_indices = (int *)malloc(new_current_alloc);
        if (new_current_indices == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free(new_used_indices);
            exit(EXIT_FAILURE);
        }
        if (current_size > 0 && current_indices != NULL) {
            if (!safe_memcpy(new_current_indices, new_current_alloc,
                             current_indices, (size_t)current_size * sizeof(int))) {
                free(new_used_indices);
                free(new_current_indices);
                continue;
            }
        }
        new_current_indices[current_size] = i;

        find_combinations_recursive(tuples, tuple_count, target_sum - tuples[i].size,
                                      new_current_indices, new_current_size,
                                      new_used_indices, new_used_size,
                                      results, result_count, max_results);

        free(new_used_indices);
        free(new_current_indices);
    }
}

Combination *find_combinations(const Tuple *tuples, int tuple_count, int target_sum, int *result_count) {
    if (tuples == NULL || tuple_count <= 0 || target_sum <= 0) {
        *result_count = 0;
        return NULL;
    }

    int max_possible = 1;
    for (int i = 0; i < tuple_count && max_possible > 0; i++) {
        if (max_possible > INT32_MAX / 2) {
            max_possible = INT32_MAX;
            break;
        }
        max_possible *= 2;
    }
    if (max_possible <= 0) max_possible = 1000;

    size_t results_alloc = (size_t)max_possible * sizeof(Combination);
    if (results_alloc / sizeof(Combination) != (size_t)max_possible) {
        *result_count = 0;
        return NULL;
    }
    Combination *results = (Combination *)malloc(results_alloc);
    if (results == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        *result_count = 0;
        return NULL;
    }

    size_t indices_alloc = (size_t)tuple_count * sizeof(int);
    if (indices_alloc / sizeof(int) != (size_t)tuple_count) {
        free(results);
        *result_count = 0;
        return NULL;
    }
    int *current_indices = (int *)malloc(indices_alloc);
    int *used_indices = (int *)malloc(indices_alloc);
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

    Combination *final_results = (Combination *)realloc(results, (size_t)(*result_count) * sizeof(Combination));
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
        {2},
        {2},
        {1},
        {1}
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