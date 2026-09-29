#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Tuple {
    int first;
    int second;
};

int find_min_product(const struct Tuple *list, size_t size) {
    if (list == NULL || size == 0) {
        return INT_MAX;
    }
    
    long long min_product = LLONG_MAX;
    
    for (size_t i = 0; i < size; i++) {
        long long product = (long long)list[i].first * (long long)list[i].second;
        if (product < min_product) {
            min_product = product;
        }
    }
    
    if (min_product > (long long)INT_MAX) {
        return INT_MAX;
    } else if (min_product < (long long)INT_MIN) {
        return INT_MIN;
    }
    
    return (int)min_product;
}

int main(void) {
    struct Tuple list[] = {{2, 3}, {1, 5}, {4, 2}, {0, 10}};
    /* Possible weaknesses found:
     *  Assignment 'size=sizeof(list)/sizeof(list[0])', assigned value is 4
     */
    size_t size = sizeof(list) / sizeof(list[0]);
    
    int result = find_min_product(list, size);
    
    /* Possible weaknesses found:
     *  Condition 'size==0' is always false [knownConditionTrueFalse]
     *  Condition 'size==0' is always false
     */
    if (result == INT_MAX && size == 0) {
        fprintf(stderr, "Error: Empty list\n");
        return EXIT_FAILURE;
    }
    
    printf("Minimum product: %d\n", result);
    
    return EXIT_SUCCESS;
}