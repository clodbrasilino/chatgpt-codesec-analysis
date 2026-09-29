#include <stdio.h>
#include <stdbool.h>

bool is_element_present(const int *list, size_t list_size, int element) {
    for (size_t i = 0; i < list_size; ++i) {
        if (list[i] == element) {
            return true;
        }
    }
    return false;
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    int element = 3;

    if (is_element_present(list, list_size, element)) {
        printf("Element %d is present in the list.\n", element);
    } else {
        printf("Element %d is not present in the list.\n", element);
    }

    return 0;
}