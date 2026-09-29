#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

static bool contains_sublist(const int *list, size_t list_len, const int *sublist, size_t sublist_len)
{
    if ((list == NULL) || (sublist == NULL)) {
        return false;
    }

    if (sublist_len == 0U) {
        return true;
    }

    if (sublist_len > list_len) {
        return false;
    }

    for (size_t i = 0U; i <= (list_len - sublist_len); i++) {
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

static void report_result(const char *label, bool found)
{
    if (found) {
        (void)printf("%s found\n", label);
    } else {
        (void)printf("%s not found\n", label);
    }
}

static void report_null_check(bool found)
{
    if (found) {
        (void)printf("NULL list check failed\n");
    } else {
        (void)printf("NULL list handled safely\n");
    }
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int sub1[] = {3, 4, 5};
    int sub2[] = {5, 4, 3};
    int sub3[] = {7, 8};

    size_t list_len = sizeof(list) / sizeof(list[0]);

    report_result("Sublist 1", contains_sublist(list, list_len, sub1, sizeof(sub1) / sizeof(sub1[0])));
    report_result("Sublist 2", contains_sublist(list, list_len, sub2, sizeof(sub2) / sizeof(sub2[0])));
    report_result("Sublist 3", contains_sublist(list, list_len, sub3, sizeof(sub3) / sizeof(sub3[0])));

    const int * volatile null_list = NULL;
    report_null_check(contains_sublist(null_list, 0U, sub1, sizeof(sub1) / sizeof(sub1[0])));

    return 0;
}