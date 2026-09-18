#include <stdio.h>

int calculate_dog_years(int human_years) {
    int dog_years = 0;
    if (human_years <= 2) {
        /* Possible weaknesses found:
         * UBSan: -5.85941e+09 is outside the range of representable values of type 'int' (AFL crash: id:000001,sig:06,src:000004,time:14595,execs:4823,op:havoc,rep:4)
         */
        dog_years = human_years * 10.5;
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1212704310 * 4 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:2779,execs:948,op:havoc,rep:4)
         */
        dog_years = 21 + (human_years - 2) * 4;
    }
    return dog_years;
}

int main() {
    int human_years;
    printf("Enter the age of the dog in human years: ");
    if (scanf("%d", &human_years) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    int dog_years = calculate_dog_years(human_years);
    printf("The dog's age in dog years is: %d\n", dog_years);
    return 0;
}