#include <stdio.h>

int calculate_dog_years(int human_years) {
    if (human_years <= 2) {
        return human_years * 10;
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1111111110 * 4 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:843,execs:305,op:havoc,rep:1)
         */
        return 20 + (human_years - 2) * 4;
    }
}

int main() {
    int human_years;
    printf("Enter the dog's age in human years: ");
    if (scanf("%d", &human_years) != 1) {
        printf("Invalid input. Please enter an integer.\n");
        return 1;
    }

    if (human_years < 0) {
        printf("Age cannot be negative.\n");
        return 1;
    }

    int dog_years = calculate_dog_years(human_years);
    printf("The dog's age in dog years is: %d\n", dog_years);
    return 0;
}