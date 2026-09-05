#include <stdio.h>
#include <stdlib.h>

long long gcd(long long a, long long b) {
    long long temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

int find_two_numbers(long long low, long long high, long long *num1, long long *num2) {
    long long i, j, l;
    
    if (low > high || low < 1 || num1 == NULL || num2 == NULL) {
        return 0;
    }
    
    for (i = 1; i <= high; i++) {
        for (j = i + 1; j <= high; j++) {
            l = lcm(i, j);
            if (l >= low && l <= high) {
                *num1 = i;
                *num2 = j;
                return 1;
            }
            if (l > high && j > i + 1) {
                break;
            }
        }
    }
    return 0;
}

int main(void) {
    long long low, high, num1, num2;
    
    if (scanf("%lld %lld", &low, &high) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (find_two_numbers(low, high, &num1, &num2)) {
        printf("%lld %lld\n", num1, num2);
    } else {
        printf("No solution exists\n");
    }
    
    return EXIT_SUCCESS;
}