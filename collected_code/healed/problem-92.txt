#include <stdio.h>

int isUndulating(int num) {
    int currDigit, prevDigit;
    int increasing, decreasing;
    
    if (num < 100) {
        return 0;
    }
    
    currDigit = num % 10;
    num /= 10;
    prevDigit = num % 10;
    
    if (currDigit > prevDigit) {
        increasing = 1;
        decreasing = 0;
    } else if (currDigit < prevDigit) {
        increasing = 0;
        decreasing = 1;
    } else {
        return 0;
    }
    
    while (num > 0) {
        currDigit = num % 10;
        num /= 10;
        
        if (increasing && currDigit >= prevDigit) {
            return 0;
        } else if (decreasing && currDigit <= prevDigit) {
            return 0;
        }
        
        prevDigit = currDigit;
        increasing = !increasing;
        decreasing = !decreasing;
    }
    
    return 1;
}

int main() {
    int num = 0;
    
    printf("Enter a number: ");
    scanf("%d", &num);
    
    if (isUndulating(num)) {
        printf("%d is an undulating number.\n", num);
    } else {
        printf("%d is not an undulating number.\n", num);
    }
    
    return 0;
}