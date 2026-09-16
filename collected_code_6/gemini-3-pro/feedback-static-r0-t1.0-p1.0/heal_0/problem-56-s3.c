#include <stdio.h>
#include <limits.h>

int reverse_number(int num) {
    long long reversed = 0;
    while (num > 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    if (reversed > INT_MAX) {
        return -1;
    }
    return (int)reversed;
}

int check_condition(int num) {
    if (num < 0) {
        return 0;
    }
    
    int reversed = reverse_number(num);
    if (reversed == -1) {
        return 0;
    }
    
    if (reversed > INT_MAX / 2) {
        return 0;
    }
    
    if (num == (2 * reversed) - 1) {
        return 1;
    }
    
    return 0;
}

int main(void) {
    int test_cases[] = {73, 11, 1, 0, -5, 19, 31};
    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (size_t i = 0; i < num_cases; i++) {
        int result = check_condition(test_cases[i]);
        if (result == 1) {
            printf("%d satisfies the condition.\n", test_cases[i]);
        } else {
            printf("%d does not satisfy the condition.\n", test_cases[i]);
        }
    }
    
    return 0;
}