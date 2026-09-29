#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool list_contains(const int *list, size_t list_len, const int *elements, size_t elements_len) {
    if (list == NULL || elements == NULL) {
        return false;
    }

    for (size_t i = 0; i < elements_len; i++) {
        for (size_t j = 0; j < list_len; j++) {
            if (elements[i] == list[j]) {
                return true;
            }
        }
    }

    return false;
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5};
    size_t list_len = sizeof(list) / sizeof(list[0]);

    int elements_a[] = {6, 7, 8};
    size_t elements_a_len = sizeof(elements_a) / sizeof(elements_a[0]);

    int elements_b[] = {9, 10, 3};
    size_t elements_b_len = sizeof(elements_b) / sizeof(elements_b[0]);

    bool result_a = list_contains(list, list_len, elements_a, elements_a_len);
    bool result_b = list_contains(list, list_len, elements_b, elements_b_len);

    printf("Result A: %s\n", result_a ? "true" : "false");
    printf("Result B: %s\n", result_b ? "true" : "false");

    const int dummy_list[] = {0};
    bool result_null = list_contains(dummy_list, 1, elements_a, elements_a_len);
    printf("Result Null: %s\n", result_null ? "true" : "false");

    return EXIT_SUCCESS;
}