#include <stdio.h>

int is_odd(int number) {
    return number & 1;
}

int main(void) {
    int number;
    
    printf("Enter an integer: ");
    scanf("%d", &number);
    
    if (is_odd(number)) {
        printf("%d is odd\n", number);
    } else {
        printf("%d is even\n", number);
    }
    
    return 0;
}