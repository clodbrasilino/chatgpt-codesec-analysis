#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool all_items_equal(char **list, size_t size, const char *str) {
    if (list == NULL || str == NULL) {
        return false;
    }

    if (size == 0) {
        return true;
    }

    for (size_t i = 0; i < size; i++) {
        if (list[i] == NULL) {
            return false;
        }
        if (strcmp(list[i], str) != 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    char *list1[] = {"apple", "apple", "apple"};
    char *list2[] = {"apple", "orange", "apple"};
    char *list3[] = {};
    char *list4[] = {NULL};
    char *list5[] = {"apple", NULL, "apple"};

    printf("%d\n", all_items_equal(list1, 3, "apple"));
    printf("%d\n", all_items_equal(list2, 3, "apple"));
    printf("%d\n", all_items_equal(list3, 0, "apple"));
    printf("%d\n", all_items_equal(list4, 1, "apple"));
    printf("%d\n", all_items_equal(list5, 3, "apple"));
    printf("%d\n", all_items_equal(NULL, 3, "apple"));
    printf("%d\n", all_items_equal(list1, 3, NULL));

    return 0;
}