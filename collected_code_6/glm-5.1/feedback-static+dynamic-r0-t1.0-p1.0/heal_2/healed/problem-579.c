#include <stdio.h>
#include <stdlib.h>

int* find_dissimilar(const int *t1, int s1, const int *t2, int s2, int *res_size) {
    int *res = (int*)malloc((s1 + s2) * sizeof(int));
    if (res == NULL) {
        *res_size = 0;
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
    int t1_0[] = {3, 6, 7, 8};
    int t2_0[] = {1, 2, 7, 10};
    int res_size_0 = 0;
    int *res_0 = find_dissimilar(t1_0, 4, t2_0, 4, &res_size_0);
    if (res_0 != NULL) {
        for (int i = 0; i < res_size_0; i++) {
            printf("%d ", res_0[i]);
        }
        printf("\n");
        free(res_0);
    }

    int t1_1[] = {1, 4, 7, 8};
    int t2_1[] = {7, 9, 11, 4};
    int res_size_1 = 0;
    int *res_1 = find_dissimilar(t1_1, 4, t2_1, 4, &res_size_1);
    if (res_1 != NULL) {
        for (int i = 0; i < res_size_1; i++) {
            printf("%d ", res_1[i]);
        }
        printf("\n");
        free(res_1);
    }

    int t1_2[] = {34, 36, 11, 25};
    int t2_2[] = {34, 100, 36, 99};
    int res_size_2 = 0;
    int *res_2 = find_dissimilar(t1_2, 4, t2_2, 4, &res_size_2);
    if (res_2 != NULL) {
        for (int i = 0; i < res_size_2; i++) {
            printf("%d ", res_2[i]);
        }
        printf("\n");
        free(res_2);
    }

    return 0;
}