#include <stdio.h>
#include <stdlib.h>

struct Pair {
    int a;
    int b;
};

int max_chain_len(struct Pair arr[], int n) {
    if (n == 0) return 0;

    int i, j, res = 0;
    int *mcl = (int *)malloc(n * sizeof(int));
    if (mcl == NULL) return 0;

    for (i = 0; i < n; i++) {
        mcl[i] = 1;
    }

    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (arr[j].b < arr[i].a && mcl[j] + 1 > mcl[i]) {
                mcl[i] = mcl[j] + 1;
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (mcl[i] > res) {
            res = mcl[i];
        }
    }

    free(mcl);
    return res;
}

int compare(const void *x, const void *y) {
    struct Pair *p1 = (struct Pair *)x;
    struct Pair *p2 = (struct Pair *)y;
    return p1->a - p2->a;
}

int main() {
    struct Pair arr[] = {{5, 24}, {15, 25}, {27, 40}, {39, 60}, {50, 90}, {91, 100}};
    int n = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, n, sizeof(struct Pair), compare);

    printf("%d\n", max_chain_len(arr, n));

    return 0;
}