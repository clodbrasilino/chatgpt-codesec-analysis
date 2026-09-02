#include <stdio.h>
#include <stdlib.h>

int *mod_lists(const int *list1, int len1, const int *list2, int len2, int *result_len) {
    if (len1 != len2 || len1 == 0) {
        *result_len = 0;
        return NULL;
    }

    int *result = (int *)malloc(len1 * sizeof(int));
    if (!result) {
        *result_len = 0;
        return NULL;
    }

    for (int i = 0; i < len1; ++i) {
        if (list2[i] == 0) {
            free(result);
            *result_len = 0;
            return NULL;
        }
        result[i] = list1[i] % list2[i];
    }

    *result_len = len1;
    return result;
}

int main() {
    int list1[] = {10, 20, 30, 40};
    int list2[] = {2, 5, 3, 8};
    int len1 = sizeof(list1) / sizeof(list1[0]);
    int len2 = sizeof(list2) / sizeof(list2[0]);
    int result_len;

    int *result = mod_lists(list1, len1, list2, len2, &result_len);

    if (result && result_len > 0) {
        for (int i = 0; i < result_len; ++i) {
            printf("%d ", result[i]);
        }
        free(result);
    } else {
        printf("Error: Result is invalid\n");
    }

    return 0;
}