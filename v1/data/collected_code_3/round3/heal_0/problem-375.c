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
    printf("Enter a multiple: ");
    scanf("%d", &multiple);
    printf("Rounded number: %d\n", roundToNearestMultiple(num, multiple));
    return 0;
}