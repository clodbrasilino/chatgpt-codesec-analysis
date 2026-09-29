#include <stdio.h>
#include <stdlib.h>

void findLargestProducts(int *list1, const int *list2, int size1, int size2, int n, long long *results) {
    for (int i = 0; i < n; i++) {
        results[i] = -9223372036854775807;
    }
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            long long temp = (long long)list1[i] * list2[j];
            if (temp > results[n-1]) {
                results[n-1] = temp;
                for (int k = n-1; k > 0 && results[k] > results[k-1]; k--) {
                    temp = results[k];
                    results[k] = results[k-1];
                    results[k-1] = temp;
                }
            }
        }
    }
}

int main() {
    int list1[] = {1, 3, 5, 7};
    /* Possible weaknesses found:
     *  Variable 'list2' can be declared as const array [constVariable]
     */
    int list2[] = {2, 4, 6, 8};
    int size1 = 4;
    int size2 = 4;
    int n = 3;
    long long *results = (long long *)malloc(n * sizeof(long long));
    if (results == NULL) return 1;
    findLargestProducts(list1, list2, size1, size2, n, results);
    for (int i = 0; i < n; i++) printf("%lld ", results[i]);
    free(results);
    return 0;
}