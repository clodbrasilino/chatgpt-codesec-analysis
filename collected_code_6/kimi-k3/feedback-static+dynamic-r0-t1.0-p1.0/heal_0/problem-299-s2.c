#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *values;
    size_t count;
} Tuple;

int max_aggregate(const Tuple *tuples, size_t num_tuples) {
    if (tuples == NULL || num_tuples == 0) {
        return INT_MIN;
    }

    int max_sum = INT_MIN;
    int found_valid = 0;

    for (size_t i = 0; i < num_tuples; i++) {
        if (tuples[i].values == NULL || tuples[i].count == 0) {
            continue;
        }

        int current_sum = 0;
        for (size_t j = 0; j < tuples[i].count; j++) {
            if (tuples[i].values[j] > 0 && current_sum > INT_MAX - tuples[i].values[j]) {
                current_sum = INT_MAX;
                break;
            }
            if (tuples[i].values[j] < 0 && current_sum < INT_MIN - tuples[i].values[j]) {
                current_sum = INT_MIN;
                break;
            }
            current_sum += tuples[i].values[j];
        }

        if (!found_valid || current_sum > max_sum) {
            max_sum = current_sum;
            found_valid = 1;
        }
    }

    return found_valid ? max_sum : INT_MIN;
}

int main(void) {
    int arr1[] = {1, 2, 3};
    int arr2[] = {10, 20};
    int arr3[] = {5, 5, 5, 5};
    int arr4[] = {-1, -2, -3};

    Tuple tuples[] = {
        {arr1, 3},
        {arr2, 2},
        {arr3, 4},
        {arr4, 3}
    };

    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    int result = max_aggregate(tuples, num_tuples);

    if (result != INT_MIN) {
        printf("Maximum aggregate: %d\n", result);
    } else {
        printf("No valid tuples found.\n");
    }

    return 0;
}