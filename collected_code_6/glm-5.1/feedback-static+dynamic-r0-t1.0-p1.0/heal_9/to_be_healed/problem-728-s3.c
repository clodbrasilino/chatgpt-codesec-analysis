#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected [30, 65, 105], got <no output>
  *  test case 1 failed: expected [6, 8, 10], got <no output>
  *  test case 0 failed: expected [25, 45, 65], got <no output>
  */

int* sum_lists(const int* a, size_t len_a, const int* b, size_t len_b, size_t* out_len) {
    size_t min_len = len_a < len_b ? len_a : len_b;
    size_t max_len = len_a > len_b ? len_a : len_b;
    *out_len = max_len;

    if (max_len == 0) {
        return NULL;
    }

    int* result = (int*)malloc(max_len * sizeof(int));
    if (result == NULL) {
        *out_len = 0;
        return NULL;
    }

    size_t i = 0;
    for (; i < min_len; ++i) {
        result[i] = a[i] + b[i];
    }

    for (; i < len_a; ++i) {
        result[i] = a[i];
    }

    for (; i < len_b; ++i) {
        result[i] = b[i];
    }

    return result;
}

int main(void) {
    int t0_a[] = {10, 15, 20, 25, 30};
    int t0_b[] = {15, 30, 45};
    size_t t0_len_a = sizeof(t0_a) / sizeof(t0_a[0]);
    size_t t0_len_b = sizeof(t0_b) / sizeof(t0_b[0]);
    size_t t0_out_len = 0;
    int* t0_result = sum_lists(t0_a, t0_len_a, t0_b, t0_len_b, &t0_out_len);
    if (t0_result != NULL) {
        printf("[");
        for (size_t i = 0; i < t0_out_len; ++i) {
            printf("%d%s", t0_result[i], i == t0_out_len - 1 ? "" : ", ");
        }
        printf("]\n");
        free(t0_result);
    } else {
        printf("[]\n");
    }

    int t1_a[] = {1, 2, 3};
    int t1_b[] = {5, 6, 7};
    size_t t1_len_a = sizeof(t1_a) / sizeof(t1_a[0]);
    size_t t1_len_b = sizeof(t1_b) / sizeof(t1_b[0]);
    size_t t1_out_len = 0;
    int* t1_result = sum_lists(t1_a, t1_len_a, t1_b, t1_len_b, &t1_out_len);
    if (t1_result != NULL) {
        printf("[");
        for (size_t i = 0; i < t1_out_len; ++i) {
            printf("%d%s", t1_result[i], i == t1_out_len - 1 ? "" : ", ");
        }
        printf("]\n");
        free(t1_result);
    } else {
        printf("[]\n");
    }

    int t2_a[] = {10, 20, 30};
    int t2_b[] = {20, 45, 75, 25, 50};
    size_t t2_len_a = sizeof(t2_a) / sizeof(t2_a[0]);
    size_t t2_len_b = sizeof(t2_b) / sizeof(t2_b[0]);
    size_t t2_out_len = 0;
    int* t2_result = sum_lists(t2_a, t2_len_a, t2_b, t2_len_b, &t2_out_len);
    if (t2_result != NULL) {
        printf("[");
        for (size_t i = 0; i < t2_out_len; ++i) {
            printf("%d%s", t2_result[i], i == t2_out_len - 1 ? "" : ", ");
        }
        printf("]\n");
        free(t2_result);
    } else {
        printf("[]\n");
    }

    return 0;
}