#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

typedef struct {
    int first;
    int second;
} Tuple;

int sum_alternate_chains(const Tuple *tuples, size_t count, int start_index, int *result) {
    long long sum = 0;
    size_t i;
    size_t start;
    
    if (result == NULL) {
        return -1;
    }
    *result = 0;
    
    if (tuples == NULL) {
        return -1;
    }
    
    if (count == 0) {
        return 0;
    }
    
    if (start_index != 0 && start_index != 1) {
        return -1;
    }
    
    start = (size_t)start_index;
    
    for (i = start; i < count; i += 2) {
        long long first = (long long)tuples[i].first;
        long long second = (long long)tuples[i].second;
        
        if (first > 0 && second > 0) {
            if (first > LLONG_MAX - second) {
                return -1;
            }
        } else if (first < 0 && second < 0) {
            if (first < LLONG_MIN - second) {
                return -1;
            }
        }
        
        long long tuple_sum = first + second;
        
        if (sum > 0 && tuple_sum > 0) {
            if (sum > LLONG_MAX - tuple_sum) {
                return -1;
            }
        } else if (sum < 0 && tuple_sum < 0) {
            if (sum < LLONG_MIN - tuple_sum) {
                return -1;
            }
        }
        
        sum += tuple_sum;
    }
    
    if (sum > INT_MAX || sum < INT_MIN) {
        return -1;
    }
    
    *result = (int)sum;
    return 0;
}

int main(void) {
    Tuple data[] = {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8},
        {9, 10}
    };
    size_t count = sizeof(data) / sizeof(data[0]);
    int result_even = 0;
    int result_odd = 0;
    
    if (sum_alternate_chains(data, count, 0, &result_even) != 0) {
        fprintf(stderr, "Error calculating even chain sum\n");
        return EXIT_FAILURE;
    }
    
    if (sum_alternate_chains(data, count, 1, &result_odd) != 0) {
        fprintf(stderr, "Error calculating odd chain sum\n");
        return EXIT_FAILURE;
    }
    
    printf("Even chain sum (indices 0, 2, 4): %d\n", result_even);
    printf("Odd chain sum (indices 1, 3): %d\n", result_odd);
    
    return EXIT_SUCCESS;
}