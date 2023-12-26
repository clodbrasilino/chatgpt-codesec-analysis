#include <stdio.h>

int calculateDogAge(int humanAge) {
    if(humanAge <= 0) {
        printf("Invalid age. Please enter a positive number.\n");
        return -1;
    }
    else if(humanAge == 1) {
        printf("The dog's age in dog's years is 15.\n");
        return 15;
    }
    else if(humanAge == 2) {
        printf("The dog's age in dog's years is 24.\n");
        return 24;
    }
    else {
        int dogYears = 24 + (humanAge - 2) * 4;
        printf("The dog's age in dog's years is %d.\n", dogYears);
        return dogYears;
    }
}

int main() {
    int age;
    printf("Enter the dog's age in human years: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'age' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &age);
    calculateDogAge(age);
    return 0;
}