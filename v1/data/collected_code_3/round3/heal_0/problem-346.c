#include <stdio.h>

int entringer(int n, int k) {
    if (n == 0 && k == 0) {
        return 1;
    } else if (k == 0) {
        return 0;
    } else {
        return entringer(n, k - 1) + entringer(n - 1, k);
    }
}

int main() {
    int n, k;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter k: ");
    scanf("%d", &k);
    printf("Entringer number e(%d, %d) is %d\n", n, k, entringer(n, k));
    return 0;
}