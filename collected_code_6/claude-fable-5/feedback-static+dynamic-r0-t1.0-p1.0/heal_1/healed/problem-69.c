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

static void report_result(bool found, const char *label)
{
    if (found) {
        printf("Sublist %s found\n", label);
    } else {
        printf("Sublist %s not found\n", label);
    }
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

    report_result(contains_sublist(list, list_len, sub1, sub1_len), "{3, 5}");
    report_result(contains_sublist(list, list_len, sub2, sub2_len), "{4, 5}");
    report_result(contains_sublist(list, list_len, sub3, sub3_len), "{2, 4, 3, 5, 7}");

    const int *null_list = NULL;
    bool null_result = contains_sublist(null_list, 0, sub1, sub1_len);
    if (null_result) {
        printf("NULL list check failed\n");
    } else {
        printf("NULL list handled safely\n");
    }

    return 0;
}