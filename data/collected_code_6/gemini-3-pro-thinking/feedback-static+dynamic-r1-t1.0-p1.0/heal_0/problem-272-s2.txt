#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int first;
    int second;
};

int* extract_rear_elements(const struct Tuple* tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return NULL;
    }

    int* rear_elements = (int*)malloc(count * sizeof(int));
    if (rear_elements == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        rear_elements[i] = tuples[i].second;
    }

    return rear_elements;
}

int main(void) {
    size_t count = 3;
    
    struct Tuple* tuples = (struct Tuple*)malloc(count * sizeof(struct Tuple));
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    tuples[0].first = 1;
    tuples[0].second = 10;
    tuples[1].first = 2;
    tuples[1].second = 20;
    tuples[2].first = 3;
    tuples[2].second = 30;

    int* extracted_rears = extract_rear_elements(tuples, count);
    if (extracted_rears == NULL) {
        free(tuples);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%d\n", extracted_rears[i]);
    }

    free(extracted_rears);
    free(tuples);

    return EXIT_SUCCESS;
}