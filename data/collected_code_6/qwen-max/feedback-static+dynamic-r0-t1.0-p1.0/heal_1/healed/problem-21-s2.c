#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void findMultiples(int n, int m) {
    if (m > 0 && n > INT_MIN / m) {
        for (int i = 1; i <= m; i++) {
            printf("%d ", i * n);
        }
        printf("\n");
    } else {
        fprintf(stderr, "Input values are too large\n");
    }
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    findMultiples(n, m);
    return 0;
}