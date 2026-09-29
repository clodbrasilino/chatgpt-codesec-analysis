#include <stdio.h>
#include <stdbool.h>

bool hasSameDigitCount(int num1, int num2) {
    int count1 = 0;
    int count2 = 0;
    
    if (num1 == 0) {
        count1 = 1;
    } else {
        if (num1 < 0) {
            num1 = -num1;
        }
        while (num1 != 0) {
            num1 /= 10;
            count1++;
        }
    }
    
    if (num2 == 0) {
        count2 = 1;
    } else {
        if (num2 < 0) {
            num2 = -num2;
        }
        while (num2 != 0) {
            num2 /= 10;
            count2++;
        }
    }
    
    return count1 == count2;
}

int main(void) {
    int num1, num2;
    
    printf("Enter two numbers: ");
    if (scanf("%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (hasSameDigitCount(num1, num2)) {
        printf("Both numbers have the same number of digits.\n");
    } else {
        printf("Numbers have different number of digits.\n");
    }
    
    return 0;
}