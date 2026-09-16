#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_digits(long long n) {
    if (n == 0) {
        return 1;
    }
    
    if (n < 0) {
        if (n == LLONG_MIN) {
            n = LLONG_MAX;
        } else {
            n = -n;
        }
    }
    
    int count = 0;
    while (n > 0) {
        count++;
        n /= 10;
    }
    
    return count;
}

int have_same_number_of_digits(long long a, long long b) {
    return count_digits(a) == count_digits(b);
}

int main(void) {
    long long num1 = 0;
    long long num2 = 0;
    
    if (scanf("%lld %lld", &num1, &num2) != 2) {
        return EXIT_FAILURE;
    }
    
    if (have_same_number_of_digits(num1, num2)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return EXIT_SUCCESS;
}