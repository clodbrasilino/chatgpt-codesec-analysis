#include <stdio.h>

int nthNonMultiple(int n, int x) {
    int count = 0;
    int num = 1;
    while (count < n) {
        if (num % x != 0) {
            count++;
        }
        num++;
    }
    return num - 1;
}

int main() {
    int n, x;
    printf("Enter the nth number to find: ");
    scanf("%d", &n);
    printf("Enter the number which should not be a multiple: ");
    scanf("%d", &x);
    printf("The %dth number in the sequence which is not a multiple of %d is: %d\n", n, x, nthNonMultiple(n, x));
    return 0;
}