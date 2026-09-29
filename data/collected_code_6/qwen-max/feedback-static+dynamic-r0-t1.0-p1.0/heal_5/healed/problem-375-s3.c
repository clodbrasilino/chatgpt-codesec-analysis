#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int round_to_nearest_multiple(int number, int multiple) {
    if (multiple == 0) {
        return 0;
    }
    int remainder = number % multiple;
    if (remainder < abs(multiple) / 2) {
        long temp = (long)number - (long)remainder;
        if (temp > INT_MAX || temp < INT_MIN) {
            return 0;
        }
        return number - remainder;
    } else {
        long temp = (long)number + (long)(multiple - remainder);
        if (temp > INT_MAX || temp < INT_MIN) {
            return 0;
        }
        return number + (multiple - remainder);
    }
}

int main() {
    int number, multiple;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        return 1;
    }
    printf("Enter the multiple: ");
    if (scanf("%d", &multiple) != 1) {
        return 1;
    }
    int result = round_to_nearest_multiple(number, multiple);
    printf("Rounded number: %d\n", result);
    return 0;
}