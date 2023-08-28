#include <stdio.h>

int roundToNearestMultiple(int number, int multiple) {
    int remainder = number % multiple;
    int result = number - remainder;

    if (remainder >= multiple / 2) {
        result += multiple;
    }

    return result;
}

int main() {
    int number = 28;
    int multiple = 5;
    printf("Number: %d\n", number);
    printf("Multiple: %d\n", multiple);
    printf("Rounded number: %d\n", roundToNearestMultiple(number, multiple));
    return 0;
}