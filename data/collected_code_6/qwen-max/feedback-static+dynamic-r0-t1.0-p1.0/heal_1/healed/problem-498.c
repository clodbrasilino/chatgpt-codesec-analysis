#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int num1 = 56;
    int num2 = 98;
    int result = gcd(num1, num2);
    printf("GCD of %d and %d is %d\n", num1, num2, result);

    int test1 = gcd(2, 2);
    int test2 = gcd(4, 6);
    int test3 = gcd(3, 9);

    if (test1 == 2 && test2 == 2 && test3 == 3) {
        printf("All test cases passed.\n");
    } else {
        printf("Some test cases failed.\n");
    }

    return 0;
}