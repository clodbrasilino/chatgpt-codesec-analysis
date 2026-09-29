#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Tuple;

bool has_all_k_elements(Tuple* tuple_list, size_t list_size, int k) {
    if (tuple_list == NULL || list_size == 0) {
        return false;
    }

    bool* found = (bool*)calloc(k, sizeof(bool));
    if (found == NULL) {
        return false;
    }

    for (size_t i = 0; i < list_size; ++i) {
        if (tuple_list[i].x >= 0 && tuple_list[i].x < k) {
            found[tuple_list[i].x] = true;
        }
        if (tuple_list[i].y >= 0 && tuple_list[i].y < k) {
            found[tuple_list[i].y] = true;
        }
    }

    bool all_found = true;
    for (int i = 0; i < k; ++i) {
        if (!found[i]) {
            all_found = false;
            break;
        }
    }

    free(found);
    return all_found;
}

int main() {
    Tuple list1[] = {{0, 1}, {1, 2}, {3, 4}};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    int k1 = 5;

    if (has_all_k_elements(list1, size1, k1)) {
        printf("List 1 has all elements from 0 to %d\n", k1 - 1);
    } else {
        printf("List 1 does not have all elements from 0 to %d\n", k1 - 1);
    }

    Tuple list2[] = {{0, 1}, {2, 3}};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    int k2 = 5;

    if (has_all_k_elements(list2, size2, k2)) {
        printf("List 2 has all elements from 0 to %d\n", k2 - 1);
    } else {
        printf("List 2 does not have all elements from 0 to %d\n", k2 - 1);
    }

    return 0;
}