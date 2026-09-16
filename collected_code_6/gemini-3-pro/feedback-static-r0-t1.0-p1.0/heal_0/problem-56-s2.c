#include <stdio.h>
#include <stdbool.h>

long long reverse_number(long long n) {
    long long reversed = 0;
    long long temp = n;
    
    if (temp < 0) {
        return -1;
    }
    
    while (temp > 0) {
        reversed = reversed * 10 + (temp % 10);
        temp /= 10;
    }
    
    return reversed;
}

bool is_one_less_than_twice_reverse(long long n) {
    if (n < 0) {
        return false;
    }
    
    long long reversed = reverse_number(n);
    if (reversed < 0) {
        return false;
    }
    
    return n == (2 * reversed - 1);
}

int main(void) {
    long long test_numbers[] = {73, 1, 0, -5, 12, 100};
    size_t num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        long long num = test_numbers[i];
        bool result = is_one_less_than_twice_reverse(num);
        if (result) {
            printf("%lld satisfies the condition.\n", num);
        } else {
            printf("%lld does not satisfy the condition.\n", num);
        }
    }
    
    return 0;
}