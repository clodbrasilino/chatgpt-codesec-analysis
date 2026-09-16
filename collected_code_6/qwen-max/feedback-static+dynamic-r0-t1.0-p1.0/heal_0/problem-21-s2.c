#include <stdio.h>
#include <stdlib.h>

void findMultiples(int n, int m) {
    for (int i = 1; i <= m; i++) {
        printf("%d ", i * n);
    }
    printf("\n");
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