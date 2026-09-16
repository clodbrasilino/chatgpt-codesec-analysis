#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'nums1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'nums2' can be declared as pointer to const [constParameterPointer]
 */
int** find_k_pairs(int* nums1, int nums1_size, int* nums2, int nums2_size, int k, int* return_size, int** return_column_sizes) {
    *return_size = 0;
    if (k <= 0 || nums1_size == 0 || nums2_size == 0) {
        *return_column_sizes = NULL;
        return NULL;
    }

    int max_pairs = nums1_size < k ? nums1_size : k;
    int** result = (int**)malloc(max_pairs * sizeof(int*));
    if (result == NULL) {
        exit(EXIT_FAILURE);
    }

    *return_column_sizes = (int*)malloc(max_pairs * sizeof(int));
    if (*return_column_sizes == NULL) {
        free(result);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < max_pairs; i++) {
        result[i] = (int*)malloc(2 * sizeof(int));
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(*return_column_sizes);
            free(result);
            exit(EXIT_FAILURE);
        }
        (*return_column_sizes)[i] = 2;
    }

    int count = 0;
    for (int i = 0; i < nums1_size && count < k; i++) {
        for (int j = 0; j < nums2_size && count < k; j++) {
            result[count][0] = nums1[i];
            result[count][1] = nums2[j];
            count++;
        }
    }

    *return_size = count;
    return result;
}

int main() {
    int nums1[] = {1, 7, 11};
    int nums2[] = {2, 4, 6};
    int k = 3;

    int return_size = 0;
    int* return_column_sizes = NULL;
    int** result = find_k_pairs(nums1, 3, nums2, 3, k, &return_size, &return_column_sizes);

    for (int i = 0; i < return_size; i++) {
        printf("[%d, %d]\n", result[i][0], result[i][1]);
        free(result[i]);
    }

    free(return_column_sizes);
    free(result);

    return 0;
}