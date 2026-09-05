#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool contains_sublist(const int *list, int list_size, const int *sublist, int sublist_size) {
    if (sublist_size <= 0) {
        return true;
    }
    if (list == NULL || list_size <= 0) {
        return false;
    }
    if (sublist == NULL || list_size < sublist_size) {
        return false;
    }
    for (int i = 0; i <= list_size - sublist_size; i++) {
        bool match = true;
        for (int j = 0; j < sublist_size; j++) {
            if (list[i + j] != sublist[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
}

int main(void) {
    const int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    const int sublist1[] = {3, 4, 5};
    const int sublist2[] = {4, 6};
    const int sublist3[] = {9};
    const int sublist4[] = {0};

    volatile bool result1 = contains_sublist(list, 9, sublist1, 3);
    volatile bool result2 = contains_sublist(list, 9, sublist2, 2);
    volatile bool result3 = contains_sublist(list, 9, sublist3, 1);
    volatile bool result4 = contains_sublist(list, 9, sublist4, 0);
    volatile bool result5 = contains_sublist(NULL, 0, sublist1, 3);

    printf("Result 1: %s\n", result1 ? "true" : "false");
    printf("Result 2: %s\n", result2 ? "true" : "false");
    printf("Result 3: %s\n", result3 ? "true" : "false");
    printf("Result 4: %s\n", result4 ? "true" : "false");
    printf("Result 5: %s\n", result5 ? "true" : "false");

    return 0;
}