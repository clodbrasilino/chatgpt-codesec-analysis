#include <stdio.h>
#include <stdlib.h>

long long calculate_ascii_sum(const char *str) {
    long long sum = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    while (*str != '\0') {
        sum += (unsigned char)(*str);
        str++;
    }
    
    return sum;
}

int main(void) {
    const char *test_string = "Hello, World!";
    long long ascii_sum = 0;
    
    ascii_sum = calculate_ascii_sum(test_string);
    
    printf("%lld\n", ascii_sum);
    
    return 0;
}