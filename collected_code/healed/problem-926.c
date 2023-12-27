#include <stdio.h>

int rencontres(int n) {
    if (n == 1 || n == 2)
        return n - 1;
    else
        return rencontres(n - 1) + rencontres(n - 2);
}

int main() {
    int n = 0;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    
    printf("The %d-th rencontres number is %d\n", n, rencontres(n));
    
    return 0;
}