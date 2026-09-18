#include <stdio.h>
#include <stdlib.h>

int dog_age_in_dog_years(int human_years) {
    if (human_years < 0) {
        return -1;
    }
    if (human_years <= 2) {
        return human_years * 10.5;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 734194470 * 4 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:658,execs:319,op:havoc,rep:2)
     */
    return 21 + (human_years - 2) * 4;
}

int main(void) {
    int human_years;
    int dog_years;
    int result;

    printf("Enter dog's age in human years: ");
    result = scanf("%d", &human_years);

    if (result != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    dog_years = dog_age_in_dog_years(human_years);

    if (dog_years < 0) {
        fprintf(stderr, "Age cannot be negative\n");
        return 1;
    }

    printf("Dog's age in dog years: %d\n", dog_years);

    return 0;
}