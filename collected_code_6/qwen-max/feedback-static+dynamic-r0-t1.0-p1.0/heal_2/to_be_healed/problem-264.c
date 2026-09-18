#include <stdio.h>
#include <limits.h>

int calculate_dog_years(int human_years) {
    if (human_years <= 2) {
        if (human_years > INT_MAX / 10 || human_years * 10.5 > INT_MAX) {
            return -1;
        }
        /* Possible weaknesses found:
         * UBSan: -2.17776e+10 is outside the range of representable values of type 'int' (AFL crash: id:000001,sig:06,src:000001,time:1489,execs:670,op:havoc,rep:1)
         */
        return (int)(human_years * 10.5 + 0.5);
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1848304524 * 4 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000004,time:640,execs:307,op:havoc,rep:9)
         */
        int temp = (human_years - 2) * 4;
        if (temp > INT_MAX - 21 || temp < INT_MIN) {
            return -1;
        }
        return 21 + temp;
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