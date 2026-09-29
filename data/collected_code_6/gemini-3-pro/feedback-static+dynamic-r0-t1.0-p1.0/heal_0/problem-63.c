#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Tuple {
    int first;
    int second;
};

int max_difference(struct Tuple* tuples, size_t size) {
    if (tuples == NULL || size == 0) {
        return -1; 
    }

    int max_diff = INT_MIN;

    for (size_t i = 0; i < size; ++i) {
        int diff = abs(tuples[i].first - tuples[i].second);
        if (diff > max_diff) {
            max_diff = diff;
        }
    }

    return max_diff;
}

int main(void) {
    size_t size = 4;
    struct Tuple* tuples = (struct Tuple*)malloc(size * sizeof(struct Tuple));
    
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    tuples[0].first = 1; tuples[0].second = 5;
    tuples[1].first = 10; tuples[1].second = 2;
    tuples[2].first = -3; tuples[2].second = 7;
    tuples[3].first = 8; tuples[3].second = 8;

    int result = max_difference(tuples, size);
    
    printf("%d\n", result);

    free(tuples);
    tuples = NULL;

    return EXIT_SUCCESS;
}