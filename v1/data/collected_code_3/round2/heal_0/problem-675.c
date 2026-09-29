#include <stdio.h>

int add(int num1, int num2, int lowerRange, int upperRange) {
    int sum = num1 + num2;
    if (sum > lowerRange && sum < upperRange) {
        return 20;
    }
    return sum;
}

int main() {
    int num1 = 5, num2 = 10, lowerRange = 10, upperRange = 20;
    printf("%d\n", add(num1, num2, lowerRange, upperRange));
    return 0;
}