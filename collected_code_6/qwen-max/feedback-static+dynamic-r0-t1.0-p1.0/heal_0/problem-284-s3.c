#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int are_all_items_equal(const char *list[], size_t list_size, const char *target) {
    for (size_t i = 0; i < list_size; ++i) {
        if (strcmp(list[i], target) != 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    const char *list1[] = {"apple", "apple", "apple"};
    const char *list2[] = {"banana", "apple", "apple"};
    const char *target = "apple";

    size_t list1_size = sizeof(list1) / sizeof(list1[0]);
    size_t list2_size = sizeof(list2) / sizeof(list2[0]);

    int result1 = are_all_items_equal(list1, list1_size, target);
    int result2 = are_all_items_equal(list2, list2_size, target);

    printf("List 1: %s\n", result1 ? "All items are equal to the target" : "Not all items are equal to the target");
    printf("List 2: %s\n", result2 ? "All items are equal to the target" : "Not all items are equal to the target");

    return 0;
}