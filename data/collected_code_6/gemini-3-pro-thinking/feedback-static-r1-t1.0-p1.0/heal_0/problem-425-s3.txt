#include <stdio.h>
#include <stdlib.h>

unsigned long long calculate_combinations(unsigned long long n) {
    if (n == 0) {
        return 0;
    }
    if (n % 2 == 0) {
        return (n / 2) * (n + 1);
    }
    return n * ((n + 1) / 2);
}

unsigned long long count_sublists_with_element(const int *array, size_t size, int target) {
    if (array == NULL || size == 0) {
        return 0;
    }

    unsigned long long total_sublists = calculate_combinations((unsigned long long)size);
    unsigned long long sublists_without_target = 0;
    unsigned long long current_segment_length = 0;

    for (size_t i = 0; i < size; ++i) {
        if (array[i] == target) {
            sublists_without_target += calculate_combinations(current_segment_length);
            current_segment_length = 0;
        } else {
            current_segment_length++;
        }
    }
    sublists_without_target += calculate_combinations(current_segment_length);

    if (total_sublists < sublists_without_target) {
        return 0;
    }

    return total_sublists - sublists_without_target;
}

int main(void) {
    const size_t array_size = 5;
    int *array = (int *)malloc(array_size * sizeof(int));
    
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 2;
    array[4] = 4;

    int target = 2;

    unsigned long long result = count_sublists_with_element(array, array_size, target);

    printf("%llu\n", result);

    free(array);
    array = NULL;

    return EXIT_SUCCESS;
}