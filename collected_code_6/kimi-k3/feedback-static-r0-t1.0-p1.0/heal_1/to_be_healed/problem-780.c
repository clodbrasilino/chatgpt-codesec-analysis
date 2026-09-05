#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int first;
    int second;
    int sum;
} TupleSum;

size_t find_combinations(const Tuple *tuples, size_t count, int target_sum, TupleSum **results) {
    size_t result_count = 0;
    size_t capacity = 10;
    TupleSum *temp_results;
    size_t i, j;
    int current_sum;

    if (tuples == NULL || results == NULL || count == 0) {
        return 0;
    }

    temp_results = (TupleSum *)malloc(capacity * sizeof(TupleSum));
    if (temp_results == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        for (j = i + 1; j < count; j++) {
            current_sum = tuples[i].first + tuples[i].second + tuples[j].first + tuples[j].second;
            if (current_sum == target_sum) {
                if (result_count >= capacity) {
                    TupleSum *new_ptr;
                    capacity *= 2;
                    new_ptr = (TupleSum *)realloc(temp_results, capacity * sizeof(TupleSum));
                    if (new_ptr == NULL) {
                        free(temp_results);
                        return 0;
                    }
                    temp_results = new_ptr;
                }
                temp_results[result_count].first = i;
                temp_results[result_count].second = j;
                temp_results[result_count].sum = current_sum;
                result_count++;
            }
        }
    }

    if (result_count == 0) {
        free(temp_results);
        *results = NULL;
        return 0;
    }

    *results = temp_results;
    return result_count;
}

int main(void) {
    Tuple tuples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {2, 3}, {4, 5}};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    int target_sum = 14;
    TupleSum *results = NULL;
    size_t result_count;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    result_count = find_combinations(tuples, count, target_sum, &results);

    if (result_count > 0 && results != NULL) {
        printf("Combinations with sum %d:\n", target_sum);
        for (i = 0; i < result_count; i++) {
            /* Possible weaknesses found:
             *  %zu in format string (no. 1) requires 'size_t' but the argument type is 'signed int'. [invalidPrintfArgType_uint]
             *  %zu in format string (no. 4) requires 'size_t' but the argument type is 'signed int'. [invalidPrintfArgType_uint]
             */
            printf("Tuple %zu (%d, %d) + Tuple %zu (%d, %d) = %d\n",
                   results[i].first,
                   tuples[results[i].first].first,
                   tuples[results[i].first].second,
                   results[i].second,
                   tuples[results[i].second].first,
                   tuples[results[i].second].second,
                   results[i].sum);
        }
        free(results);
    } else {
        printf("No combinations found with sum %d.\n", target_sum);
    }

    return 0;
}