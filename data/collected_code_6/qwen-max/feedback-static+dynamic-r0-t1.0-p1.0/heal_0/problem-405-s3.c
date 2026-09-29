#include <stdio.h>
#include <stdbool.h>

bool check_element_in_tuple(const int *tuple, size_t tuple_size, int element) {
    for (size_t i = 0; i < tuple_size; ++i) {
        if (tuple[i] == element) {
            return true;
        }
    }
    return false;
}

int main() {
    const int tuple[] = {1, 2, 3, 4, 5};
    const size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    int element_to_find = 3;

    bool is_found = check_element_in_tuple(tuple, tuple_size, element_to_find);
    if (is_found) {
        printf("Element %d found in the tuple.\n", element_to_find);
    } else {
        printf("Element %d not found in the tuple.\n", element_to_find);
    }

    return 0;
}