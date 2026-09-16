#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int minOpsToEqual(int x, int y) {
    int g = gcd(x, y);
    return (x / g + y / g - 2);
}

int main() {
    int a = 10, b = 15;
    printf("Minimum operations required: %d\n", minOpsToEqual(a, b));
    return 0;
}