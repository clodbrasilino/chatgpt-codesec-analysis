#include <stdio.h>
#include <stdlib.h>

struct Pair {
    int a;
    int b;
};

int compare_pairs(const void *x, const void *y) {
    const struct Pair *p1 = (const struct Pair *)x;
    const struct Pair *p2 = (const struct Pair *)y;
    if (p1->a != p2->a) {
        return p1->a - p2->a;
    }
    return p1->b - p2->b;
}

int longest_chain(struct Pair arr[], int n) {
    if (n == 0) {
        return 0;
    }
    qsort(arr, n, sizeof(struct Pair), compare_pairs);
    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return 0;
    }
    int max_len = 1;
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j].b < arr[i].a && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
        }
    }
    free(dp);
    return max_len;
}

int main() {
    struct Pair arr1[] = {{5, 24}, {39, 60}, {15, 28}, {27, 40}, {50, 90}};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", longest_chain(arr1, n1));

    struct Pair arr2[] = {{1, 2}, {2, 3}, {3, 4}};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", longest_chain(arr2, n2));

    return 0;
}