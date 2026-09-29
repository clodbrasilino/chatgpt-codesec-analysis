#include <stdio.h>
#include <stdlib.h>

int* modulo_lists(const int *list1, int len1, const int *list2, int len2, int *result_len) {
    if (len1 != len2) return NULL;
    *result_len = len1;
    int *result = (int *)malloc(len1 * sizeof(int));
    if (result == NULL) return NULL;
    for (int i = 0; i < len1; ++i) {
        result[i] = list1[i] % list2[i];
    }
    return result;
}

int main() {
    int list1[] = {10, 20, 30, 40, 50};
    int list2[] = {3, 5, 7, 9, 11};
    int len1 = sizeof(list1) / sizeof(list1[0]);
    int len2 = sizeof(list2) / sizeof(list2[0]);
    int result_len;
    int *result = modulo_lists(list1, len1, list2, len2, &result_len);
    if (result != NULL) {
        for (int i = 0; i < result_len; ++i) {
            printf("%d ", result[i]);
        }
        free(result);
    } else {
        printf("Error: Lists are of different lengths or memory allocation failed.\n");
    }
    return 0;
}