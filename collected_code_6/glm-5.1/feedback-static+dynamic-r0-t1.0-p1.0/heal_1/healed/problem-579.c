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
    int *temp = (int*)realloc(res, count * sizeof(int));
    if (temp != NULL) {
        res = temp;
    }
    *res_size = count;
    return res;
}

int main() {
    int t1[] = {1, 2, 3, 4};
    int t2[] = {3, 4, 5, 6};
    int s1 = sizeof(t1) / sizeof(t1[0]);
    int s2 = sizeof(t2) / sizeof(t2[0]);
    int res_size = 0;
    int *res = find_dissimilar(t1, s1, t2, s2, &res_size);
    if (res != NULL) {
        for (int i = 0; i < res_size; i++) {
            printf("%d ", res[i]);
        }
        printf("\n");
        free(res);
    }
    return 0;
}