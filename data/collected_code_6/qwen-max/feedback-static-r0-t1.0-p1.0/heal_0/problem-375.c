#include <stdio.h>
#include <math.h>

int round_to_nearest_multiple(int number, int multiple) {
    if (multiple == 0) {
        return number;
    }
    return (int)round((double)number / multiple) * multiple;
}

int main() {
    int number = 123;
    int multiple = 10;
    int result = round_to_nearest_multiple(number, multiple);
    printf("Rounded number: %d\n", result);
    return 0;
}