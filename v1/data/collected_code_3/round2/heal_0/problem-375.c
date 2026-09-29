#include <stdio.h>

int roundToNearestMultiple(int num, int multiple) {
    int remainder = num % multiple;
    if (remainder == 0)
        return num;
    return num + multiple - remainder;
}

int main() {
    int num, multiple;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Enter the multiple to which you want to round the number: ");
    scanf("%d", &multiple);
    printf("The rounded number is: %d\n", roundToNearestMultiple(num, multiple));
    return 0;
}