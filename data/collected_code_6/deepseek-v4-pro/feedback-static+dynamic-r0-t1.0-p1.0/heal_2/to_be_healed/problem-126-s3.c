#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int sum_common_divisors(int a, int b) {
    int g = gcd(abs(a), abs(b));
    int sum = 0;
    int sqrt_g = (int)sqrt(g);
    
    for (int i = 1; i <= sqrt_g; i++) {
        if (g % i == 0) {
            sum += i;
            int other = g / i;
            if (other != i) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 1944444437 + 222222220 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:938,execs:667,op:havoc,rep:8)
                 * UBSan: signed integer overflow: 1773790891 + 886895444 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000018,time:19293,execs:13063,op:havoc,rep:2)
                 * UBSan: signed integer overflow: 2073078823 + 77177700 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:1801,execs:1238,op:havoc,rep:15)
                 */
                sum += other;
            }
        }
    }
    
    return sum;
}

int main(void) {
    int a, b;
    
    printf("Enter two integers: ");
    if (scanf("%d %d", &a, &b) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (a == 0 && b == 0) {
        fprintf(stderr, "Both numbers cannot be zero\n");
        return 1;
    }
    
    int result = sum_common_divisors(a, b);
    printf("Sum of common divisors: %d\n", result);
    
    return 0;
}