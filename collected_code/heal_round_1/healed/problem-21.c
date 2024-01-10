#include <stdio.h>

void findMultiples(int n, int m) {
    for (int i = 1; i <= m; i++) {
        printf("%d ", n * i);
    }
}

int main() {
    int n = 0, m = 0;
    
    printf("Enter the number: ");
    scanf("%d", &n);
    
    printf("Enter the number of multiples to find: ");
    scanf("%d", &m);
    
    findMultiples(n, m);
    
    return 0;
}