#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool contains_any(const int *list1, size_t len1, const int *list2, size_t len2)
{
    if (list1 == NULL || list2 == NULL) {
        return false;
    }

    for (size_t i = 0; i < len1; i++) {
        for (size_t j = 0; j < len2; j++) {
            if (list1[i] == list2[j]) {
                return true;
            }
        }
    }

    return false;
}

int main(void)
{
    int list1[] = { 1, 3, 5, 7, 9 };
    int list2[] = { 2, 4, 6, 8, 9 };
    int list3[] = { 10, 12, 14 };

    size_t len1 = sizeof(list1) / sizeof(list1[0]);
    size_t len2 = sizeof(list2) / sizeof(list2[0]);
    size_t len3 = sizeof(list3) / sizeof(list3[0]);

    if (contains_any(list1, len1, list2, len2)) {
        printf("At least one element of list2 is present in list1.\n");
    } else {
        printf("No element of list2 is present in list1.\n");
    }

    if (contains_any(list1, len1, list3, len3)) {
        printf("At least one element of list3 is present in list1.\n");
    } else {
        printf("No element of list3 is present in list1.\n");
    }

    return EXIT_SUCCESS;
}