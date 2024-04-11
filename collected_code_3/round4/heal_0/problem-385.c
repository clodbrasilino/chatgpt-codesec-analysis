#include <stdio.h>

int perrin(int n) {
    if(n == 0) return 3;
    if(n == 1 || n == 2) return 2;
    return perrin(n - 2) + perrin(n - 3);
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %d'th Perrin number is: %d\n", n, perrin(n));
    return 0;
}