#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_abundant(int n) {
    if (n <= 0) {
        return false;
    }
    
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    
    return sum > n;
}

int main(void) {
    int number;
    
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (is_abundant(number)) {
        printf("%d is an abundant number\n", number);
    } else {
        printf("%d is not an abundant number\n", number);
    }
    
    return EXIT_SUCCESS;
}