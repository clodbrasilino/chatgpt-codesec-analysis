#include <stdio.h>

int calculate_dog_age(int human_years) {
    if (human_years <= 0) {
        return -1;
    }
    if (human_years == 1) {
        return 15;
    }
    if (human_years == 2) {
        return 24;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1111111109 * 5 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000006,time:2152,execs:1121,op:havoc,rep:6)
     */
    return 24 + (human_years - 2) * 5;
}

int main(void) {
    int human_years;
    int dog_years;
    
    printf("Enter dog's age in human years: ");
    if (scanf("%d", &human_years) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    dog_years = calculate_dog_age(human_years);
    if (dog_years == -1) {
        fprintf(stderr, "Age must be greater than 0\n");
        return 1;
    }
    
    printf("Dog's age in dog years: %d\n", dog_years);
    
    return 0;
}