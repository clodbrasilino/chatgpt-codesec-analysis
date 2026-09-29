#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    int sum;
} Pair;

int compare(const void *a, const void *b) {
    return ((Pair *)a)->sum - ((Pair *)b)->sum;
}

int find_k_pairs(const int *arr1, int len1, const int *arr2, int len2, int k, Pair **result) {
    if (arr1 == NULL || len1 <= 0 || arr2 == NULL || len2 <= 0 || k <= 0) {
        *result = NULL;
        return 0;
    }

    int total_pairs = len1 * len2;
    int pairs_to_find = k < total_pairs ? k : total_pairs;

    Pair *pairs = (Pair *)malloc(pairs_to_find * sizeof(Pair));
    if (pairs == NULL) {
        *result = NULL;
        return 0;
    }

    if (pairs_to_find == total_pairs) {
        int idx = 0;
        for (int i = 0; i < len1; ++i) {
            for (int j = 0; j < len2; ++j) {
                pairs[idx].a = arr1[i];
                pairs[idx].b = arr2[j];
                pairs[idx].sum = arr1[i] + arr2[j];
                ++idx;
            }
        }
        qsort(pairs, pairs_to_find, sizeof(Pair), compare);
    } else {
        int *idx2 = (int *)calloc(len1, sizeof(int));
        if (idx2 == NULL) {
            free(pairs);
            *result = NULL;
            return 0;
        }

        for (int count = 0; count < pairs_to_find; ++count) {
            int min_sum = 0;
            int min_idx = -1;

            for (int i = 0; i < len1; ++i) {
                if (idx2[i] < len2) {
                    int current_sum = arr1[i] + arr2[idx2[i]];
                    if (min_idx == -1 || current_sum < min_sum) {
                        min_sum = current_sum;
                        min_idx = i;
                    }
                }
            }

            if (min_idx == -1) {
                pairs_to_find = count;
                break;
            }

            pairs[count].a = arr1[min_idx];
            pairs[count].b = arr2[idx2[min_idx]];
            pairs[count].sum = min_sum;
            idx2[min_idx]++;
        }

        free(idx2);
    }

    *result = pairs;
    return pairs_to_find;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'arr1' can be declared as const array [constVariable]
     */
    int arr1[] = {1, 7, 11};
    /* Possible weaknesses found:
     *  Variable 'arr2' can be declared as const array [constVariable]
     */
    int arr2[] = {2, 4, 6};
    int k = 3;

    Pair *result = NULL;
    int result_len = find_k_pairs(arr1, 3, arr2, 3, k, &result);

    if (result != NULL) {
        for (int i = 0; i < result_len; ++i) {
            printf("[%d, %d]", result[i].a, result[i].b);
            if (i < result_len - 1) {
                printf(", ");
            }
        }
        printf("\n");
        free(result);
    }

    return 0;
}