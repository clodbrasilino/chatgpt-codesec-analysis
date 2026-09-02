#include <stdio.h>
#include <stdlib.h>

void find_dissimilar(const int *tuple1, const int *tuple2, int len1, int len2, int *result, int *result_len) {
    *result_len = 0;
    for (int i = 0; i < len1; ++i) {
        int found = 0;
        for (int j = 0; j < len2; ++j) {
            if (tuple1[i] == tuple2[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            result[(*result_len)++] = tuple1[i];
        }
    }
    for (int i = 0; i < len2; ++i) {
        int found = 0;
        for (int j = 0; j < len1; ++j) {
            if (tuple2[i] == tuple1[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            result[(*result_len)++] = tuple2[i];
        }
    }
}

int main() {
    int tuple1[] = {1, 2, 3, 4};
    int tuple2[] = {3, 4, 5, 6};
    int len1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int len2 = sizeof(tuple2) / sizeof(tuple2[0]);
    int *result = (int *)malloc((len1 + len2) * sizeof(int));
    int result_len;

    find_dissimilar(tuple1, tuple2, len1, len2, result, &result_len);

    for (int i = 0; i < result_len; ++i) {
        printf("%d ", result[i]);
    }
    free(result);
    return 0;
}