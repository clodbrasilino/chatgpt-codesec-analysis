#include <stdio.h>

int multiply(int a, int b) {
    unsigned int ua = (unsigned int)a;
    unsigned int ub = (unsigned int)b;
    unsigned int result = 0;

    while (ub != 0) {
        if (ub & 1) {
            result += ua;
        }
        ua <<= 1;
        ub >>= 1;
    }

    return (int)result;
}

int main(void) {
    int a = 15;
    int b = -7;
    int result = multiply(a, b);
    
    printf("%d\n", result);
    
    return 0;
}