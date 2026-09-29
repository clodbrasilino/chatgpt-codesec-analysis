#include <stdio.h>
#include <stdlib.h>

int find_gcd(int num1, int num2) {
    if (num2 == 0) {
        return abs(num1);
    }
    return find_gcd(num2, num1 % num2);
}

int main(void) {
    int a = 48;
    int b = 18;
    int gcd = find_gcd(a, b);

    printf("%d\n", gcd);

    return 0;
}