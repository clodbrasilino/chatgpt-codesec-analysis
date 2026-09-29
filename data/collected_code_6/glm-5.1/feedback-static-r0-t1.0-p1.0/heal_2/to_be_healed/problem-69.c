#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool contains_sublist(const int *list, size_t list_len, const int *sublist, size_t sublist_len) {
    if (list == NULL || sublist == NULL) {
        return false;
    }
    if (sublist_len == 0) {
        return true;
    }
    if (sublist_len > list_len) {
        return false;
    }
    for (size_t i = 0; i <= list_len - sublist_len; i++) {
        bool match = true;
        for (size_t j = 0; j < sublist_len; j++) {
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
    int sub1[] = {3, 4, 5};
    int sub2[] = {1, 6};
    /* Possible weaknesses found:
     *  Variable 'sub3' can be declared as const array [constVariable]
     */
    int sub3[] = {};
    int sub4[] = {2, 3};
    
    size_t len1 = sizeof(list1) / sizeof(list1[0]);
    size_t slen1 = sizeof(sub1) / sizeof(sub1[0]);
    size_t slen2 = sizeof(sub2) / sizeof(sub2[0]);
    size_t slen3 = 0;
    size_t slen4 = sizeof(sub4) / sizeof(sub4[0]);

    printf("%d\n", contains_sublist(list1, len1, sub1, slen1));
    printf("%d\n", contains_sublist(list1, len1, sub2, slen2));
    printf("%d\n", contains_sublist(list1, len1, sub3, slen3));
    printf("%d\n", contains_sublist(list1, len1, sub4, slen4));

    return 0;
}