#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'elements' can be declared as pointer to const [constParameterPointer]
 */
bool is_element_present(int *list, size_t list_size, int *elements, size_t elements_size) {
    if (list == NULL || elements == NULL || list_size == 0 || elements_size == 0) {
        return false;
    }

    for (size_t i = 0; i < elements_size; i++) {
        for (size_t j = 0; j < list_size; j++) {
            if (elements[i] == list[j]) {
                return true;
            }
        }
    }

    return false;
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5};
    size_t list_size = sizeof(list) / sizeof(list[0]);

    int elements_a[] = {6, 7, 8};
    size_t elements_a_size = sizeof(elements_a) / sizeof(elements_a[0]);

    int elements_b[] = {9, 10, 2};
    size_t elements_b_size = sizeof(elements_b) / sizeof(elements_b[0]);

    int empty_list[] = {0};
    size_t empty_list_size = 0;

    bool result_one = is_element_present(list, list_size, elements_a, elements_a_size);
    bool result_two = is_element_present(list, list_size, elements_b, elements_b_size);
    bool result_three = is_element_present(empty_list, empty_list_size, elements_a, elements_a_size);
    bool result_four = is_element_present(list, list_size, NULL, elements_a_size);

    printf("Result one: %s\n", result_one ? "true" : "false");
    printf("Result two: %s\n", result_two ? "true" : "false");
    printf("Result three: %s\n", result_three ? "true" : "false");
    printf("Result four: %s\n", result_four ? "true" : "false");

    return EXIT_SUCCESS;
}