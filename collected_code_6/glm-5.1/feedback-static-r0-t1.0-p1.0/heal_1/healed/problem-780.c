#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    int size;
} Tuple;

typedef struct {
    int *combination;
    int size;
} CombinationResult;

int check_sum(const Tuple *tuples, const int *indices, int k, int target) {
    int sum = 0;
    for (int i = 0; i < k; i++) {
        if (indices[i] >= tuples[i].size) {
            return 0;
        }
        sum += tuples[i].values[indices[i]];
    }
    return sum == target;
}

void find_combinations_recursive(const Tuple *tuples, int num_tuples, int target, int *indices, int k, CombinationResult **results, int *result_count, int *result_capacity) {
    if (k == num_tuples) {
        if (check_sum(tuples, indices, k, target)) {
            if (*result_count >= *result_capacity) {
                *result_capacity *= 2;
                CombinationResult *temp = realloc(*results, *result_capacity * sizeof(CombinationResult));
                if (!temp) {
                    exit(EXIT_FAILURE);
                }
                *results = temp;
            }
            (*results)[*result_count].combination = malloc(num_tuples * sizeof(int));
            if (!(*results)[*result_count].combination) {
                exit(EXIT_FAILURE);
            }
            for (int i = 0; i < num_tuples; i++) {
                (*results)[*result_count].combination[i] = indices[i];
            }
            (*results)[*result_count].size = num_tuples;
            (*result_count)++;
        }
        return;
    }

    for (int i = 0; i < tuples[k].size; i++) {
        indices[k] = i;
        find_combinations_recursive(tuples, num_tuples, target, indices, k + 1, results, result_count, result_capacity);
    }
}

CombinationResult* find_combinations(const Tuple *tuples, int num_tuples, int target, int *result_count) {
    int *indices = malloc(num_tuples * sizeof(int));
    if (!indices) {
        exit(EXIT_FAILURE);
    }

    int result_capacity = 16;
    CombinationResult *results = malloc(result_capacity * sizeof(CombinationResult));
    if (!results) {
        free(indices);
        exit(EXIT_FAILURE);
    }

    *result_count = 0;
    find_combinations_recursive(tuples, num_tuples, target, indices, 0, &results, result_count, &result_capacity);
    
    free(indices);
    return results;
}

void free_results(CombinationResult *results, int result_count) {
    for (int i = 0; i < result_count; i++) {
        free(results[i].combination);
    }
    free(results);
}

int main() {
    int arr0[] = {1, 2};
    int arr1[] = {3, 4};
    int arr2[] = {5, 6};

    Tuple tuples[] = {
        {arr0, 2},
        {arr1, 2},
        {arr2, 2}
    };

    int num_tuples = 3;
    int target = 10;
    int result_count = 0;

    CombinationResult *results = find_combinations(tuples, num_tuples, target, &result_count);

    for (int i = 0; i < result_count; i++) {
        printf("(");
        for (int j = 0; j < results[i].size; j++) {
            int tuple_idx = j;
            int val_idx = results[i].combination[j];
            printf("%d", tuples[tuple_idx].values[val_idx]);
            if (j < results[i].size - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    free_results(results, result_count);

    return 0;
}