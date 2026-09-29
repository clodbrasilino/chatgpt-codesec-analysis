#include <stdio.h>
#include <stdlib.h>

int* find_dissimilar(const int* t1, int s1, const int* t2, int s2, int* res_size) {
    *res_size = 0;
    int* res = (int*)malloc((s1 + s2) * sizeof(int));
    if (!res) {
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
    if (count == 0) {
        free(res);
        return NULL;
    }
    int* tmp = (int*)realloc(res, count * sizeof(int));
    if (tmp) {
        res = tmp;
    }
    *res_size = count;
    return res;
}

int main() {
    int t1_0[] = {3, 6, 7, 10};
    int t2_0[] = {3, 6, 8, 9};
    int s1_0 = sizeof(t1_0) / sizeof(t1_0[0]);
    int s2_0 = sizeof(t2_0) / sizeof(t2_0[0]);
    int res_size_0 = 0;
    int* res_0 = find_dissimilar(t1_0, s1_0, t2_0, s2_0, &res_size_0);
    if (res_0 != NULL) {
        printf("[");
        for (int i = 0; i < res_size_0; i++) {
            printf("%d%s", res_0[i], (i == res_size_0 - 1) ? "" : ", ");
        }
        printf("]\n");
        free(res_0);
    }

    int t1_1[] = {1, 4, 7, 9};
    int t2_1[] = {1, 4, 5, 8};
    int s1_1 = sizeof(t1_1) / sizeof(t1_1[0]);
    int s2_1 = sizeof(t2_1) / sizeof(t2_1[0]);
    int res_size_1 = 0;
    int* res_1 = find_dissimilar(t1_1, s1_1, t2_1, s2_1, &res_size_1);
    if (res_1 != NULL) {
        printf("[");
        for (int i = 0; i < res_size_1; i++) {
            printf("%d%s", res_1[i], (i == res_size_1 - 1) ? "" : ", ");
        }
        printf("]\n");
        free(res_1);
    }

    int t1_2[] = {34, 36, 11, 25};
    int t2_2[] = {34, 36, 11, 22};
    int s1_2 = sizeof(t1_2) / sizeof(t1_2[0]);
    int s2_2 = sizeof(t2_2) / sizeof(t2_2[0]);
    int res_size_2 = 0;
    int* res_2 = find_dissimilar(t1_2, s1_2, t2_2, s2_2, &res_size_2);
    if (res_2 != NULL) {
        printf("[");
        for (int i = 0; i < res_size_2; i++) {
            printf("%d%s", res_2[i], (i == res_size_2 - 1) ? "" : ", ");
        }
        printf("]\n");
        free(res_2);
    }

    return 0;
}