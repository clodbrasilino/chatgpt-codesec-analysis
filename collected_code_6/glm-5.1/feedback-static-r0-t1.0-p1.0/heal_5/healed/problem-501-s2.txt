#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int find_common_divisor(int a, int b) {
    if (a == 0 && b == 0) {
        return 0;
    }
    
    a = abs(a);
    b = abs(b);
    
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
}

int main(int argc, char * const argv[const]) {
    int num1, num2;
    
    if (argc != 3) {
        return 1;
    }
    
    size_t len1 = strnlen(argv[1], 12);
    if (len1 > 11) {
        return 1;
    }
    
    size_t len2 = strnlen(argv[2], 12);
    if (len2 > 11) {
        return 1;
    }
    
    char *endptr1;
    errno = 0;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (errno != 0 || *endptr1 != '\0' || val1 < INT_MIN || val1 > INT_MAX) {
        return 1;
    }
    num1 = (int)val1;

    char *endptr2;
    errno = 0;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (errno != 0 || *endptr2 != '\0' || val2 < INT_MIN || val2 > INT_MAX) {
        return 1;
    }
    num2 = (int)val2;
    
    int result = find_common_divisor(num1, num2);
    printf("%d\n", result);
    
    return 0;
}