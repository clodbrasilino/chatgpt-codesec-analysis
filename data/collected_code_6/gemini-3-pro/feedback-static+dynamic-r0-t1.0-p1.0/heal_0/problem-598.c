#include <stdio.h>
#include <math.h>

int countDigits(int n) {
    int count = 0;
    while (n != 0) {
        count++;
        n /= 10;
    }
    return count;
}

int isArmstrong(int n) {
    if (n < 0) {
        return 0;
    }
    
    int originalNum = n;
    int numDigits = countDigits(n);
    int sum = 0;
    
    while (n != 0) {
        int remainder = n % 10;
        sum += pow(remainder, numDigits);
        n /= 10;
    }
    
    return (sum == originalNum);
}

int main() {
    int num;
    
    if (scanf("%d", &num) != 1) {
        return 1;
    }
    
    if (isArmstrong(num)) {
        printf("%d is an Armstrong number.\n", num);
    } else {
        printf("%d is not an Armstrong number.\n", num);
    }
    
    return 0;
}