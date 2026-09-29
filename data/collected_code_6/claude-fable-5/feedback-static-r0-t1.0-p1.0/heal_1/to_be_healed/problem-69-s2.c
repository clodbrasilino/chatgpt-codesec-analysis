#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool contains_sublist(const int *list, size_t list_len, const int *sublist, size_t sublist_len)
{
    if (list == NULL || sublist == NULL) {
        return false;
    }

    if (sublist_len == 0U) {
        return true;
    }

    if (sublist_len > list_len) {
        return false;
    }

    for (size_t i = 0U; i <= list_len - sublist_len; i++) {
        size_t j;
        for (j = 0U; j < sublist_len; j++) {
            if (list[i + j] != sublist[j]) {
                break;
            }
        }
        if (j == sublist_len) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int sub1[] = {3, 4, 5};
    int sub2[] = {5, 4, 3};
    int sub3[] = {7, 8};

    size_t list_len = sizeof(list) / sizeof(list[0]);

    if (contains_sublist(list, list_len, sub1, sizeof(sub1) / sizeof(sub1[0]))) {
        (void)printf("Sublist 1 found\n");
    } else {
        (void)printf("Sublist 1 not found\n");
    }

    if (contains_sublist(list, list_len, sub2, sizeof(sub2) / sizeof(sub2[0]))) {
        (void)printf("Sublist 2 found\n");
    } else {
        (void)printf("Sublist 2 not found\n");
    }

    if (contains_sublist(list, list_len, sub3, sizeof(sub3) / sizeof(sub3[0]))) {
        (void)printf("Sublist 3 found\n");
    } else {
        (void)printf("Sublist 3 not found\n");
    }

    /* Possible weaknesses found:
     *  Condition 'contains_sublist(NULL,0U,sub1,sizeof(sub1)/sizeof(sub1[0]))' is always false
     *  Condition 'contains_sublist(NULL,0U,sub1,sizeof(sub1)/sizeof(sub1[0]))' is always false [knownConditionTrueFalse]
     *  Calling function 'contains_sublist' returns 0
     */
    if (contains_sublist(NULL, 0U, sub1, sizeof(sub1) / sizeof(sub1[0]))) {
        (void)printf("NULL list check failed\n");
    } else {
        (void)printf("NULL list handled safely\n");
    }

    return 0;
}