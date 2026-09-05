#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int all_items_equal(char **list, size_t size, const char *str) {
    if (list == NULL || str == NULL) {
        return 0;
    }

    if (size == 0) {
        return 1;
    }

    for (size_t i = 0; i < size; ++i) {
        if (list[i] == NULL) {
            return 0;
        }

        if (strcmp(list[i], str) != 0) {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    char *list1[] = {"apple", "apple", "apple"};
    char *list2[] = {"apple", "banana", "apple"};
    char *list3[] = {NULL, "apple"};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    size_t size3 = sizeof(list3) / sizeof(list3[0]);

    printf("%d\n", all_items_equal(list1, size1, "apple"));
    printf("%d\n", all_items_equal(list2, size2, "apple"));
    printf("%d\n", all_items_equal(list3, size3, "apple"));
    printf("%d\n", all_items_equal(NULL, size1, "apple"));
    printf("%d\n", all_items_equal(list1, 0, "apple"));
    printf("%d\n", all_items_equal(list1, size1, NULL));

    return 0;
}