#include <stdio.h>
#include <stdlib.h>

long long gcd_ll(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int find_lcm_pair(long long low, long long high, long long *num1, long long *num2) {
    if (num1 == NULL || num2 == NULL || low > high || low < 1) {
        return 0;
    }
    
    for (long long a = low; a <= high; a++) {
        for (long long b = a + 1; b <= high; b++) {
            long long g = gcd_ll(a, b);
            if (g == 0) continue;
            
            if (a > high / (b / g)) {
                continue;
            }
            
            long long lcm = (a / g) * b;
            
            if (lcm >= low && lcm <= high) {
                *num1 = a;
                *num2 = b;
                return 1;
            }
        }
    }
    return 0;
}

int main(void) {
    long long low, high;
    long long num1, num2;
    
    printf("Enter range (low high): ");
    if (scanf("%lld %lld", &low, &high) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (find_lcm_pair(low, high, &num1, &num2)) {
        printf("Found pair: %lld and %lld\n", num1, num2);
        printf("LCM: %lld\n", (num1 / gcd_ll(num1, num2)) * num2);
    } else {
        printf("No pair found with LCM in range [%lld, %lld]\n", low, high);
    }
    
    return EXIT_SUCCESS;
}