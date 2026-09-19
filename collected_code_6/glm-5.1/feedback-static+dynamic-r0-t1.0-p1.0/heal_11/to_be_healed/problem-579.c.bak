#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected [1, 4, 7, 9], got <no output>
  *  test case 2 failed: expected [34, 36, 11, 25], got <no output>
  *  test case 0 failed: expected [3, 6, 7, 10], got <no output>
  */

int* find_dissimilar(const int *t1, int s1, const int *t2, int s2, int *res_size) {
    *res_size = 0;
    if (s1 <= 0 || s2 <= 0) {
        return NULL;
    }
    int *res = (int*)malloc((s1 + s2) * sizeof(int));
    if (res == NULL) {
        return NULL;
    }
    int count = 0;
    for (int i = 0; i < s1; i++) {
        int found = 0;
        for (int j = 0; j < s2; j++) {
            if (t1[i] == t2[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            res[count++] = t1[i];
        }
    }
    for (int i = 0; i < s2; i++) {
        int found = 0;
        for (int j = 0; j < s1; j++) {
            if (t2[i] == t1[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            res[count++] = t2[i];
        }
    }
    if (count > 0) {
        int *temp = (int*)realloc(res, count * sizeof(int));
        if (temp != NULL) {
            res = temp;
        }
    } else {
        free(res);
        res = NULL;
    }
    *res_size = count;
    return res;
}

int main() {
    const int t1_0[] = {3, 6, 7, 8};
    const int t2_0[] = {1, 2, 7, 10};
    int res_size_0;
    int *res_0 = find_dissimilar(t1_0, 4, t2_0, 4, &res_size_0);
    printf("[");
    if (res_0 != NULL && res_size_0 > 0) {
        for (int i = 0; i < res_size_0; i++) {
            printf("%d", res_0[i]);
            if (i < res_size_0 - 1) printf(", ");
        }
        free(res_0);
    }
    printf("]\n");

    const int t1_1[] = {1, 4, 7, 8};
    const int t2_1[] = {7, 9, 11, 4};
    int res_size_1;
    int *res_1 = find_dissimilar(t1_1, 4, t2_1, 4, &res_size_1);
    printf("[");
    if (res_1 != NULL && res_size_1 > 0) {
        for (int i = 0; i < res_size_1; i++) {
            printf("%d", res_1[i]);
            if (i < res_size_1 - 1) printf(", ");
        }
        free(res_1);
    }
    printf("]\n");

    const int t1_2[] = {34, 36, 11, 25};
    const int t2_2[] = {34, 100, 36, 99};
    int res_size_2;
    int *res_2 = find_dissimilar(t1_2, 4, t2_2, 4, &res_size_2);
    printf("[");
    if (res_2 != NULL && res_size_2 > 0) {
        for (int i = 0; i < res_size_2; i++) {
            printf("%d", res_2[i]);
            if (i < res_size_2 - 1) printf(", ");
        }
        free(res_2);
    }
    printf("]\n");

    fflush(stdout);

    return 0;
}