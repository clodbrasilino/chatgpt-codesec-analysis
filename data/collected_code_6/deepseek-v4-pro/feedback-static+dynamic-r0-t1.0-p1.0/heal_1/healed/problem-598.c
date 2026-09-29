#include <stdio.h>
#include <math.h>

int is_armstrong(int number) {
    int original;
    int result = 0;
    int digits = 0;

    if (number < 0) {
        return 0;
    }

    original = number;
    while (original != 0) {
        original /= 10;
        digits++;
    }

    original = number;
    while (original != 0) {
        int remainder = original % 10;
        long long power = 1;
        int i;
        
        for (i = 0; i < digits; i++) {
            power *= remainder;
            if (power > 2147483647LL) {
                return 0;
            }
        }
        
        if (result > 2147483647 - (int)power) {
            return 0;
        }
        result += (int)power;
        original /= 10;
    }

    return result == number;
}

int main() {
    int num;

    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (is_armstrong(num)) {
        printf("%d is an Armstrong number\n", num);
    } else {
        printf("%d is not an Armstrong number\n", num);
    }

    return 0;
}