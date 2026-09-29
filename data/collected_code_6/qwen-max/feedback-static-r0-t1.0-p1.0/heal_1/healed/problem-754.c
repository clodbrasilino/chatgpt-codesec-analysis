#include <stdio.h>
#include <stdlib.h>

int* find_common_index(const int *list1, const int *list2, const int *list3, int size, int *result_size) {
    int *common = (int *)malloc(size * sizeof(int));
    if (common == NULL) return NULL;

    *result_size = 0;

    for (int i = 0; i < size; ++i) {
        if (list1[i] == list2[i] && list2[i] == list3[i]) {
            common[(*result_size)++] = list1[i];
        }
    }

    if (*result_size > 0) {
        int *temp = (int *)realloc(common, (*result_size) * sizeof(int));
        if (temp == NULL) {
            free(common);
            return NULL;
        }
        common = temp;
    } else {
        free(common);
        common = NULL;
    }

    return common;
}

int main() {
    int list1[] = {1, 2, 3, 4};
    int list2[] = {1, 2, 5, 4};
    int list3[] = {1, 8, 3, 4};
    int size = 4;
    int result_size = 0;

    int *common = find_common_index(list1, list2, list3, size, &result_size);

    if (common != NULL) {
        for (int i = 0; i < result_size; ++i) {
            printf("%d ", common[i]);
        }
        free(common);
    } else {
        printf("No common elements found.\n");
    }

    return 0;
}