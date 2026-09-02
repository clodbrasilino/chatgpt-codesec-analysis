#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    
    int limit = (int)sqrt((double)n);
    for (int i = 5; i <= limit; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int numbers[] = {0, 1, 2, 3, 4, 5, 16, 17, 25, 97, 100, 101};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    
    for (size_t i = 0; i < count; i++) {
        printf("%d is %sprime\n", numbers[i], is_prime(numbers[i]) ? "" : "not ");
    }
    
    return 0;
}