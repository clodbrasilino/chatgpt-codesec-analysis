#include <stdio.h>
#include <stdlib.h>

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
    
    if (sscanf(argv[1], "%d", &num1) != 1) {
        return 1;
    }
    
    if (sscanf(argv[2], "%d", &num2) != 1) {
        return 1;
    }
    
    int result = find_common_divisor(num1, num2);
    printf("%d\n", result);
    
    return 0;
}