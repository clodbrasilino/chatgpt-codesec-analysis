#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

int main() {
    int x, y;
    printf("Enter two positive integers: ");
    scanf("%d %d", &x, &y);
    if (x > 0 && y > 0) {
        printf("LCM of %d and %d is %d\n", x, y, lcm(x, y));
    } else {
        printf("Please enter positive integers.\n");
    }
    return 0;
}