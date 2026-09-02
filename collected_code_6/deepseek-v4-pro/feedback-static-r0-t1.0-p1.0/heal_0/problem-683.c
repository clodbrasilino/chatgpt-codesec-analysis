#include <stdio.h>
#include <math.h>

int is_sum_of_two_squares(int n) {
    if (n < 0) return 0;
    
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int count = 0;
            while (n % i == 0) {
                count++;
                n /= i;
            }
            if (i % 4 == 3 && count % 2 != 0) {
                return 0;
            }
        }
    }
    
    if (n > 1 && n % 4 == 3) {
        return 0;
    }
    
    return 1;
}

int main() {
    int test_cases[] = {0, 1, 2, 4, 5, 8, 10, 13, 16, 17, 18, 20, 25, 32, 41, 50, 65, 85, 100, 7, 15, 21, 23, 28, 31, 39, 43, 47, 55, 63, 71, 79, 87};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        if (is_sum_of_two_squares(test_cases[i])) {
            printf("%d can be represented as sum of two squares\n", test_cases[i]);
        } else {
            printf("%d cannot be represented as sum of two squares\n", test_cases[i]);
        }
    }
    
    return 0;
}