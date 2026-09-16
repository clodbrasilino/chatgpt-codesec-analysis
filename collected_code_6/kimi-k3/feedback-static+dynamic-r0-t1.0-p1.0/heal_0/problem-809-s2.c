#include <stdio.h>
#include <stdbool.h>

#define TUPLE_SIZE 5

bool check_tuple_elements(const int first_tuple[], const int second_tuple[], size_t size) {
    if (first_tuple == NULL || second_tuple == NULL || size == 0) {
        return false;
    }

    for (size_t i = 0; i < size; i++) {
        if (second_tuple[i] >= first_tuple[i]) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int first_tuple[TUPLE_SIZE] = {10, 20, 30, 40, 50};
    int second_tuple[TUPLE_SIZE] = {5, 15, 25, 35, 45};

    if (check_tuple_elements(first_tuple, second_tuple, TUPLE_SIZE)) {
        printf("All elements of the second tuple are smaller than the corresponding elements of the first tuple.\n");
    } else {
        printf("Not all elements of the second tuple are smaller than the corresponding elements of the first tuple.\n");
    }

    return 0;
}