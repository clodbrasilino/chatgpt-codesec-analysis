#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool check_all_equal(char **list, size_t list_size, const char *target) {
    if (list == NULL || target == NULL) {
        return false;
    }

    if (list_size == 0) {
        return true;
    }

    for (size_t i = 0; i < list_size; i++) {
        if (list[i] == NULL) {
            return false;
        }
        if (strcmp(list[i], target) != 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const char *target = "apple";
    size_t size1 = 3;
    char **list1 = malloc(size1 * sizeof(char *));
    
    if (list1 == NULL) {
        return 1;
    }

    list1[0] = strdup("apple");
    list1[1] = strdup("apple");
    list1[2] = strdup("apple");

    if (list1[0] == NULL || list1[1] == NULL || list1[2] == NULL) {
        free(list1[0]);
        free(list1[1]);
        free(list1[2]);
        free(list1);
        return 1;
    }

    if (check_all_equal(list1, size1, target)) {
        printf("List 1: All items are equal to '%s'.\n", target);
    } else {
        printf("List 1: Not all items are equal to '%s'.\n", target);
    }

    free(list1[0]);
    free(list1[1]);
    free(list1[2]);
    free(list1);

    size_t size2 = 3;
    char **list2 = malloc(size2 * sizeof(char *));
    
    if (list2 == NULL) {
        return 1;
    }

    list2[0] = strdup("apple");
    list2[1] = strdup("orange");
    list2[2] = strdup("apple");

    if (list2[0] == NULL || list2[1] == NULL || list2[2] == NULL) {
        free(list2[0]);
        free(list2[1]);
        free(list2[2]);
        free(list2);
        return 1;
    }

    if (check_all_equal(list2, size2, target)) {
        printf("List 2: All items are equal to '%s'.\n", target);
    } else {
        printf("List 2: Not all items are equal to '%s'.\n", target);
    }

    free(list2[0]);
    free(list2[1]);
    free(list2[2]);
    free(list2);

    return 0;
}