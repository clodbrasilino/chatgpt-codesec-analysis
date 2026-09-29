#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool all_items_equal(const char *const *list, size_t count, const char *target)
{
    size_t i;

    if (list == NULL || target == NULL) {
        return false;
    }

    for (i = 0; i < count; i++) {
        if (list[i] == NULL) {
            return false;
        }
        if (strcmp(list[i], target) != 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const char *list1[] = { "apple", "apple", "apple" };
    const char *list2[] = { "apple", "banana", "apple" };
    const size_t count1 = sizeof(list1) / sizeof(list1[0]);
    const size_t count2 = sizeof(list2) / sizeof(list2[0]);
    const char *target = "apple";

    if (all_items_equal(list1, count1, target)) {
        printf("All items in list1 are equal to \"%s\"\n", target);
    } else {
        printf("Not all items in list1 are equal to \"%s\"\n", target);
    }

    if (all_items_equal(list2, count2, target)) {
        printf("All items in list2 are equal to \"%s\"\n", target);
    } else {
        printf("Not all items in list2 are equal to \"%s\"\n", target);
    }

    return EXIT_SUCCESS;
}