#include <stdio.h>

void findMultiples(int n, int m) {
    for (int i = 1; i <= m; i++) {
        printf("%d ", n * i);
    }
}

int main() {
    int n, m;
    
    printf("Enter the number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    
    printf("Enter the number of multiples to find: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'm' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &m);
    
    findMultiples(n, m);
    
    return 0;
}