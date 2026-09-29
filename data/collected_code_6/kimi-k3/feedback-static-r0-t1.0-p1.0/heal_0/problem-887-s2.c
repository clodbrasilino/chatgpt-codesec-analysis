#include <stdio.h>

int is_odd(int num) {
    return num & 1;
}

int main(void) {
    int number;
    int result;
    
    if (scanf("%d", &number) != 1) {
        return 1;
    }
    
    result = is_odd(number);
    
    if (result == 1) {
        printf("%d is odd\n", number);
    } else {
        printf("%d is even\n", number);
    }
    
    return 0;
}