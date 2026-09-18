#include <stdio.h>

unsigned long long tetrahedral_number(int n) {
    return (n * (n + 1) * (n + 2)) / 6;
}

int main() {
    int n;
    unsigned long long t;
    
    printf("Enter a number: ");
    scanf("%d", &n);
    
    if(n < 0){
        printf("Negative input is not allowed.\n");
        return -1;
    }
    
    t = tetrahedral_number(n);
    
    if (t == 0 && n != 0) {
        printf("Overflow occurred for input %d.\n", n);
        return -1;
    }

    printf("Tetrahedral number for %d is: %llu\n", n, t);
    
    return 0;
}