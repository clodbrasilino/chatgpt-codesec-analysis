#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_sum_of_two_squares(int n) {
    if (n < 0) return false;
    
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int count = 0;
            while (n % i == 0) {
                n /= i;
                count++;
            }
            if (i % 4 == 3 && count % 2 != 0) {
                return false;
            }
        }
    }
    
    if (n > 1 && n % 4 == 3) {
        return false;
    }
    
    return true;
}

int main(void) {
    int test_cases[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 13, 18, 25, 34, 41, 50, 65, 85, 100, 130};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        int num = test_cases[i];
        if (is_sum_of_two_squares(num)) {
            printf("%d can be represented as sum of two squares\n", num);
        } else {
            printf("%d cannot be represented as sum of two squares\n", num);
        }
    }
    
    return 0;
}