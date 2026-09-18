#include <stdio.h>
#include <stdbool.h>

bool is_difference_of_squares(long long n) {
    unsigned long long un = (unsigned long long)n;
    if (un % 4 != 2) {
        return true;
    }
    return false;
}

int main(void) {
    long long num = 0;
    
    if (scanf("%lld", &num) != 1) {
        return 1;
    }
    
    if (is_difference_of_squares(num)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return 0;
}