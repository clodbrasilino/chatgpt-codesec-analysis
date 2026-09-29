#include <stdio.h>
#include <stdlib.h>

int e(int n, int k) {
    if (k == 0 || k == n) return 1;
    if (k > n) return 0;
    return e(n-1, k-1) + e(n-1, k) + e(n-1, k+1);
}

int main() {
    int n, k;
    printf("Enter n and k: ");
    if (scanf("%d %d", &n, &k) != 2) {
        return 1;
    }
    printf("e(%d, %d) = %d\n", n, k, e(n, k));
    return 0;
}