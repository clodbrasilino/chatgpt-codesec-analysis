#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected [30, 65, 105], got <no output>
  *  test case 0 failed: expected [25, 45, 65], got <no output>
  *  test case 1 failed: expected [6, 8, 10], got <no output>
  */

int* sum_lists(const int* a, size_t a_len, const int* b, size_t b_len, size_t* out_len) {
    if (a == NULL || b == NULL || out_len == NULL) {
        return NULL;
    }

    size_t min_len = a_len < b_len ? a_len : b_len;
    size_t max_len = a_len > b_len ? a_len : b_len;
    *out_len = max_len;

    int* result = (int*)malloc(*out_len * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    size_t i;
    for (i = 0; i < min_len; ++i) {
        result[i] = a[i] + b[i];
    }

    for (; i < max_len; ++i) {
        if (i < a_len) {
            result[i] = a[i];
        } else {
            result[i] = b[i];
        }
    }

    return result;
}

int main(void) {
    int a0[] = {10, 15, 20, 25};
    int b0[] = {15, 30, 45};
    size_t a0_len = sizeof(a0) / sizeof(a0[0]);
    size_t b0_len = sizeof(b0) / sizeof(b0[0]);
    size_t out0_len = 0;
    int* result0 = sum_lists(a0, a0_len, b0, b0_len, &out0_len);
    if (result0 != NULL && out0_len > 0) {
        printf("[");
        for (size_t i = 0; i < out0_len; ++i) {
            printf("%d%s", result0[i], i < out0_len - 1 ? ", " : "");
        }
        printf("]\n");
        free(result0);
    } else {
        printf("<no output>\n");
    }

    int a1[] = {1, 2, 3, 4};
    int b1[] = {5, 6, 7};
    size_t a1_len = sizeof(a1) / sizeof(a1[0]);
    size_t b1_len = sizeof(b1) / sizeof(b1[0]);
    size_t out1_len = 0;
    int* result1 = sum_lists(a1, a1_len, b1, b1_len, &out1_len);
    if (result1 != NULL && out1_len > 0) {
        printf("[");
        for (size_t i = 0; i < out1_len; ++i) {
            printf("%d%s", result1[i], i < out1_len - 1 ? ", " : "");
        }
        printf("]\n");
        free(result1);
    } else {
        printf("<no output>\n");
    }

    int a2[] = {20, 35, 50, 65, 80};
    int b2[] = {10, 30, 55};
    size_t a2_len = sizeof(a2) / sizeof(a2[0]);
    size_t b2_len = sizeof(b2) / sizeof(b2[0]);
    size_t out2_len = 0;
    int* result2 = sum_lists(a2, a2_len, b2, b2_len, &out2_len);
    if (result2 != NULL && out2_len > 0) {
        printf("[");
        for (size_t i = 0; i < out2_len; ++i) {
            printf("%d%s", result2[i], i < out2_len - 1 ? ", " : "");
        }
        printf("]\n");
        free(result2);
    } else {
        printf("<no output>\n");
    }

    return EXIT_SUCCESS;
}