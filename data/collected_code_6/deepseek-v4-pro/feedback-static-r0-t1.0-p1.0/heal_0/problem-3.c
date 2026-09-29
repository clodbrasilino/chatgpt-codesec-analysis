#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_non_prime(int n) {
    if (n <= 1) {
        return true;
    }
    if (n == 2) {
        return false;
    }
    if (n % 2 == 0) {
        return true;
    }
    int limit = (int)sqrt((double)n);
    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0) {
            return true;
        }
    }
    return false;
}

int main(void) {
    int test_values[] = {0, 1, 2, 3, 4, 5, 9, 15, 17, 25, 29, 49, 97, 100};
    int count = sizeof(test_values) / sizeof(test_values[0]);
    
    for (int i = 0; i < count; i++) {
        printf("%d is %s\n", test_values[i], 
               is_non_prime(test_values[i]) ? "non-prime" : "prime");
    }
    
    return 0;
}