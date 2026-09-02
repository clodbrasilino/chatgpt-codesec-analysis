#include <stdio.h>
#include <stdbool.h>

bool is_abundant(int n) {
    if (n <= 1) {
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
    int numbers[] = {12, 18, 20, 28, 6, 10, 0, -12, 1};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    for (int i = 0; i < size; i++) {
        printf("%d is %sabundant\n", numbers[i], 
               is_abundant(numbers[i]) ? "" : "not ");
    }
    
    return 0;
}