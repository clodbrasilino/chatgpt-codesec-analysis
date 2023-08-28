#include <stdbool.h>
#include <stdio.h>

bool isKeithNumber(int num) {
    int temp = num;
    int numDigits = 0;
    while (temp > 0) {
        numDigits++;
        temp /= 10;
    }
    
    int sequence[numDigits];
    temp = num;
    for (int i = numDigits - 1; i >= 0; i--) {
        sequence[i] = temp % 10;
        temp /= 10;
    }
    
    int nextNum = num;
    while (nextNum < num) {
        int sum = 0;
        for (int i = 0; i < numDigits; i++) {
            sum += sequence[i];
        }
        
        if (sum == num) {
            return true;
        }
        
        for (int i = 0; i < numDigits - 1; i++) {
            sequence[i] = sequence[i+1];
        }
        sequence[numDigits - 1] = sum;
        
        nextNum = 0;
        for (int i = 0; i < numDigits; i++) {
            nextNum = nextNum * 10 + sequence[i];
        }
    }
    
    return false;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (isKeithNumber(num)) {
        printf("%d is a Keith number.", num);
    } else {
        printf("%d is not a Keith number.", num);
    }

    return 0;
}