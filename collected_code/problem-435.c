#include <stdio.h>

int lastDigit(int number) {
    return number % 10;
}

int main() {
    int number = 1234567890;
    int last = lastDigit(number);
    printf("Last digit: %d\n", last);
    
    return 0;
}