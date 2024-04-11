#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void findNumbers(int l, int r) {
    int i, j;
    for (i = l; i <= r; i++) {
        for (j = i + 1; j <= r; j++) {
            if ((i * j) / gcd(i, j) <= r) {
                printf("%d %d\n", i, j);
                return;
            }
        }
    }
    printf("No suitable numbers found\n");
}

int main() {
    int l = 1, r = 10;
    findNumbers(l, r);
    return 0;
}