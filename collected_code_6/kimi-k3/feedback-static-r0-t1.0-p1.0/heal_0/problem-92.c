#include <stdio.h>
#include <stdbool.h>

bool isUndulating(long long number) {
    if (number < 0) {
        number = -number;
    }
    
    if (number < 100) {
        return false;
    }
    
    int digits[20];
    int count = 0;
    long long temp = number;
    
    while (temp > 0) {
        digits[count] = (int)(temp % 10);
        temp /= 10;
        count++;
    }
    
    for (int i = 0; i < count / 2; i++) {
        int tempDigit = digits[i];
        digits[i] = digits[count - 1 - i];
        digits[count - 1 - i] = tempDigit;
    }
    
    int firstDigit = digits[0];
    int secondDigit = digits[1];
    
    if (firstDigit == secondDigit) {
        return false;
    }
    
    for (int i = 2; i < count; i++) {
        int expectedDigit = (i % 2 == 0) ? firstDigit : secondDigit;
        if (digits[i] != expectedDigit) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    long long number;
    
    printf("Enter a number: ");
    
    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (isUndulating(number)) {
        printf("%lld is an undulating number.\n", number);
    } else {
        printf("%lld is not an undulating number.\n", number);
    }
    
    return 0;
}