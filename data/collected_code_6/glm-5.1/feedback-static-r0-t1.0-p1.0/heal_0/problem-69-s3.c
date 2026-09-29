#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool contains_sublist(int *list, int list_size, int *sublist, int sublist_size) {
    if (sublist_size == 0) {
        return true;
    }
    if (list_size < sublist_size || list == NULL || sublist == NULL) {
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
    int list1[] = {1, 2, 3, 4, 5, 6};
    int sublist1[] = {3, 4, 5};
    int list2[] = {1, 2, 3, 4, 5, 6};
    int sublist2[] = {4, 6};
    int list3[] = {1, 2, 3};
    int sublist3[] = {1, 2, 3};
    int list4[] = {1, 2, 3};
    int sublist4[] = {1, 2, 3, 4};
    int list5[] = {1, 2, 3};
    int sublist5[] = {};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t subsize1 = sizeof(sublist1) / sizeof(sublist1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    size_t subsize2 = sizeof(sublist2) / sizeof(sublist2[0]);
    size_t size3 = sizeof(list3) / sizeof(list3[0]);
    size_t subsize3 = sizeof(sublist3) / sizeof(sublist3[0]);
    size_t size4 = sizeof(list4) / sizeof(list4[0]);
    size_t subsize4 = sizeof(sublist4) / sizeof(sublist4[0]);
    size_t size5 = sizeof(list5) / sizeof(list5[0]);
    size_t subsize5 = sizeof(sublist5) / sizeof(sublist5[0]);
    printf("Test 1: %d\n", contains_sublist(list1, (int)size1, sublist1, (int)subsize1));
    printf("Test 2: %d\n", contains_sublist(list2, (int)size2, sublist2, (int)subsize2));
    printf("Test 3: %d\n", contains_sublist(list3, (int)size3, sublist3, (int)subsize3));
    printf("Test 4: %d\n", contains_sublist(list4, (int)size4, sublist4, (int)subsize4));
    printf("Test 5: %d\n", contains_sublist(list5, (int)size5, sublist5, (int)subsize5));
    return 0;
}