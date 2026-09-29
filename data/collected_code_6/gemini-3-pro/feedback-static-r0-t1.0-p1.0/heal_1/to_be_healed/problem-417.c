#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    /* Possible weaknesses found:
     *  struct member 'Tuple::second' is never used. [unusedStructMember]
     */
    int second;
} Tuple;

int find_common_first_element(Tuple* tuples, size_t num_tuples, int* result) {
    if (tuples == NULL || result == NULL || num_tuples == 0) {
        return 0;
    }

    int common_element = tuples[0].first;

    for (size_t i = 1; i < num_tuples; i++) {
        if (tuples[i].first != common_element) {
            return 0;
        }
    }

    *result = common_element;
    return 1;
}

int main(void) {
    Tuple tuples[] = {
        {5, 10},
        {5, 20},
        {5, 30},
        {5, 40}
    };
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    int result = 0;

    if (find_common_first_element(tuples, num_tuples, &result)) {
        printf("Common first element: %d\n", result);
    } else {
        printf("No common first element found or invalid input.\n");
    }

    Tuple tuples_no_match[] = {
        {5, 10},
        {6, 20},
        {5, 30}
    };
    size_t num_tuples_no_match = sizeof(tuples_no_match) / sizeof(tuples_no_match[0]);

    if (find_common_first_element(tuples_no_match, num_tuples_no_match, &result)) {
        printf("Common first element: %d\n", result);
    } else {
        printf("No common first element found or invalid input.\n");
    }

    return EXIT_SUCCESS;
}