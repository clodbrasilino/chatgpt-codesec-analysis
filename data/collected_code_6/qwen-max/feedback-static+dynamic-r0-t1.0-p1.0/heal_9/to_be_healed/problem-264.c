#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int calculate_dog_years(int human_years) {
    if (human_years <= 2) {
        /* Possible weaknesses found:
         * UBSan: -5.85941e+09 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000001,time:728,execs:344,op:havoc,rep:8)
         */
        return (int)(((long long)human_years * 10.5 + 0.5));
    } else {
        long long temp = (long long)(human_years - 2) * 4;
        if (temp > INT_MAX - 21 || temp < INT_MIN) {
            return -1;
        }
        return 21 + (int)temp;
    }
}

int main() {
    int human_years;
    printf("Enter the age of the dog in human years: ");
    if (scanf("%d", &human_years) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    int dog_years = calculate_dog_years(human_years);
    if (dog_years == -1) {
        printf("Result out of range for 'int' type.\n");
    } else {
        printf("The dog's age in dog years is: %d\n", dog_years);
    }
    return 0;
}