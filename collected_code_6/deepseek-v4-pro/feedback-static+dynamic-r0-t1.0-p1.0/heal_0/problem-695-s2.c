#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool check_tuple_elements(const int *first_tuple, size_t first_size, const int *second_tuple, size_t second_size) {
    if (first_tuple == NULL || second_tuple == NULL) {
        return false;
    }

    if (first_size != second_size) {
        return false;
    }

    for (size_t i = 0; i < first_size; ++i) {
        if (second_tuple[i] <= first_tuple[i]) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int first_tuple[] = {1, 5, 3, 7, 9};
    int second_tuple[] = {2, 6, 4, 8, 10};
    size_t tuple_size = sizeof(first_tuple) / sizeof(first_tuple[0]);

    if (check_tuple_elements(first_tuple, tuple_size, second_tuple, tuple_size)) {
        printf("All elements of the second tuple are greater than corresponding elements in the first tuple.\n");
    } else {
        printf("Not all elements of the second tuple are greater than corresponding elements in the first tuple.\n");
    }

    return 0;
}