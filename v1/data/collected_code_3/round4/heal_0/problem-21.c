#include <stdio.h>

void findMultiples(int n, int m) {
    for(int i = 1; i <= m; i++) {
        printf("%d ", n * i);
    }
    printf("\n");
}

int main() {
    int n, m;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Enter the number of multiples: ");
    scanf("%d", &m);
    findMultiples(n, m);
    return 0;
}