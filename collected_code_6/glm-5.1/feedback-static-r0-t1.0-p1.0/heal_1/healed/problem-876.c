#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

unsigned int lcm(int a, int b) {
    if (a <= 0 || b <= 0) {
        exit(EXIT_FAILURE);
    }
    return (unsigned int)a / gcd(a, b) * (unsigned int)b;
}

int main(void) {
    int a, b;
    if (scanf("%d %d", &a, &b) != 2) {
        return EXIT_FAILURE;
    }
    printf("%u\n", lcm(a, b));
    return EXIT_SUCCESS;
}