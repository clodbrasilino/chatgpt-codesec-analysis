#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int* find_common_elements(int** lists, const int* sizes, int num_lists, int* out_count) {
    if (!lists || !sizes || num_lists <= 0 || !out_count) {
        if (out_count) {
            *out_count = 0;
        }
        return NULL;
    }

    if (sizes[0] == 0) {
        *out_count = 0;
        return NULL;
    }

    int* common = (int*)malloc((size_t)sizes[0] * sizeof(int));
    if (!common) {
        *out_count = 0;
        return NULL;
    }

    int count = 0;

    for (int i = 0; i < sizes[0]; i++) {
        int candidate = lists[0][i];
        bool found_in_all = true;

        for (int j = 1; j < num_lists; j++) {
            bool found_in_current = false;
            if (!lists[j]) {
                found_in_all = false;
                break;
            }
            for (int k = 0; k < sizes[j]; k++) {
                if (lists[j][k] == candidate) {
                    found_in_current = true;
                    break;
                }
            }
            if (!found_in_current) {
                found_in_all = false;
                break;
            }
        }

        if (found_in_all) {
            bool already_added = false;
            for (int m = 0; m < count; m++) {
                if (common[m] == candidate) {
                    already_added = true;
                    break;
                }
            }
            if (!already_added) {
                common[count] = candidate;
                count++;
            }
        }
    }

    *out_count = count;

    if (count == 0) {
        free(common);
        return NULL;
    }

    int* resized = (int*)realloc(common, (size_t)count * sizeof(int));
    return resized ? resized : common;
}

int main(void) {
    int list1[] = {1, 5, 9, 3, 7, 2, 8};
    int list2[] = {2, 7, 5, 8, 10};
    int list3[] = {8, 5, 2, 11, 7};

    int* lists[] = {list1, list2, list3};
    /* Possible weaknesses found:
     *  Variable 'sizes' can be declared as const array [constVariable]
     */
    int sizes[] = {7, 5, 5};
    int num_lists = 3;

    int out_count = 0;
    int* common_elements = find_common_elements(lists, sizes, num_lists, &out_count);

    if (common_elements) {
        for (int i = 0; i < out_count; i++) {
            printf("%d\n", common_elements[i]);
        }
        free(common_elements);
    }

    return 0;
}