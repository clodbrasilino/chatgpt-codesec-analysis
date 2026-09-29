#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool contains_sublist(const int *list, size_t list_len, const int *sublist, size_t sub_len)
{
    if (list == NULL || sublist == NULL) {
        return false;
    }
    if (sub_len == 0) {
        return true;
    }
    if (sub_len > list_len) {
        return false;
    }
    for (size_t i = 0; i <= list_len - sub_len; i++) {
        size_t j;
        for (j = 0; j < sub_len; j++) {
            if (list[i + j] != sublist[j]) {
                break;
            }
        }
        if (j == sub_len) {
            return true;
        }
    }
    return false;
}

int main(void)
{
    int list[] = {2, 4, 3, 5, 7};
    size_t list_len = sizeof(list) / sizeof(list[0]);

    int sub1[] = {3, 5};
    size_t sub1_len = sizeof(sub1) / sizeof(sub1[0]);

    int sub2[] = {4, 5};
    size_t sub2_len = sizeof(sub2) / sizeof(sub2[0]);

    int sub3[] = {2, 4, 3, 5, 7};
    size_t sub3_len = sizeof(sub3) / sizeof(sub3[0]);

    if (contains_sublist(list, list_len, sub1, sub1_len)) {
        printf("Sublist {3, 5} found\n");
    } else {
        printf("Sublist {3, 5} not found\n");
    }

    if (contains_sublist(list, list_len, sub2, sub2_len)) {
        printf("Sublist {4, 5} found\n");
    } else {
        printf("Sublist {4, 5} not found\n");
    }

    if (contains_sublist(list, list_len, sub3, sub3_len)) {
        printf("Sublist {2, 4, 3, 5, 7} found\n");
    } else {
        printf("Sublist {2, 4, 3, 5, 7} not found\n");
    }

    /* Possible weaknesses found:
     *  Condition 'contains_sublist(NULL,0,sub1,sub1_len)' is always false
     *  Condition 'contains_sublist(NULL,0,sub1,sub1_len)' is always false [knownConditionTrueFalse]
     *  Calling function 'contains_sublist' returns 0
     */
    if (contains_sublist(NULL, 0, sub1, sub1_len)) {
        printf("NULL list check failed\n");
    } else {
        printf("NULL list handled safely\n");
    }

    return 0;
}