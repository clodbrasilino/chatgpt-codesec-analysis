#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int sum_of_common_divisors(int a, int b) {
    if (a == 0 && b == 0) {
        return 0;
    }
    
    int g = gcd(a, b);
    if (g == 0) {
        return 0;
    }
    
    int sum = 0;
    for (int i = 1; i <= g; i++) {
        if (g % i == 0) {
            sum += i;
        }
    }
    
    return sum;
}

int main(void) {
    int num1 = 12;
    int num2 = 18;
    
    int sum = sum_of_common_divisors(num1, num2);
    printf("%d\n", sum);
    
    return 0;
}