#include <stdio.h>
#include <stdbool.h>

bool are_elements_unique(const int *list, size_t size) {
    if (list == NULL) {
        return size < 2;
    }

    if (size < 2) {
        return true;
    }

    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (list[i] == list[j]) {
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);

    if (are_elements_unique(list1, size1)) {
        printf("List 1 elements are unique.\n");
    } else {
        printf("List 1 elements are not unique.\n");
    }

    int list2[] = {1, 2, 3, 2, 5};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);

    if (are_elements_unique(list2, size2)) {
        printf("List 2 elements are unique.\n");
    } else {
        printf("List 2 elements are not unique.\n");
    }

    const int *list3 = NULL;
    size_t size3 = 0;

    if (are_elements_unique(list3, size3)) {
        printf("List 3 elements are unique.\n");
    } else {
        printf("List 3 elements are not unique.\n");
    }

    return 0;
}