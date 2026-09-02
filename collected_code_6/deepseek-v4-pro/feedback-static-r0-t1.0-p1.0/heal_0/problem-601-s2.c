#include <stdio.h>
#include <stdlib.h>

struct Pair {
    int first;
    int second;
};

int compare_pairs(const void *a, const void *b) {
    struct Pair *pa = (struct Pair *)a;
    struct Pair *pb = (struct Pair *)b;
    if (pa->first != pb->first)
        return pa->first - pb->first;
    return pa->second - pb->second;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longest_chain(struct Pair *pairs, int n) {
    if (pairs == NULL || n <= 0) {
        return 0;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    qsort(pairs, n, sizeof(struct Pair), compare_pairs);

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (pairs[j].second < pairs[i].first) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    int max_len = 1;
    for (int i = 0; i < n; i++) {
        if (dp[i] > max_len) {
            max_len = dp[i];
        }
    }

    free(dp);
    return max_len;
}

int main(void) {
    struct Pair pairs1[] = {{5, 24}, {39, 60}, {15, 28}, {27, 40}, {50, 90}};
    int n1 = sizeof(pairs1) / sizeof(pairs1[0]);
    printf("Longest chain length for set 1: %d\n", longest_chain(pairs1, n1));

    struct Pair pairs2[] = {{5, 10}, {1, 11}, {2, 3}, {4, 5}};
    int n2 = sizeof(pairs2) / sizeof(pairs2[0]);
    printf("Longest chain length for set 2: %d\n", longest_chain(pairs2, n2));

    struct Pair pairs3[] = {{1, 2}};
    int n3 = sizeof(pairs3) / sizeof(pairs3[0]);
    printf("Longest chain length for set 3: %d\n", longest_chain(pairs3, n3));

    struct Pair pairs4[] = {{1, 2}, {2, 3}, {3, 4}};
    int n4 = sizeof(pairs4) / sizeof(pairs4[0]);
    printf("Longest chain length for set 4: %d\n", longest_chain(pairs4, n4));

    struct Pair pairs5[] = {{5, 10}, {1, 2}, {8, 9}, {3, 4}};
    int n5 = sizeof(pairs5) / sizeof(pairs5[0]);
    printf("Longest chain length for set 5: %d\n", longest_chain(pairs5, n5));

    printf("Longest chain length for NULL: %d\n", longest_chain(NULL, 5));
    printf("Longest chain length for n=0: %d\n", longest_chain(pairs1, 0));

    return 0;
}