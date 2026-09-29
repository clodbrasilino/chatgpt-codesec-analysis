#include <stdio.h>
#include <stdlib.h>

void findDemloNumber(int num) {
    int original = num;
    int sum = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'digit' can be reduced. [variableScope]
     */
    int digit;
    int temp = num;
    int isValid = 1;

    if (num < 0) {
        printf("Please enter a positive number.\n");
        return;
    }

    while (temp != 0) {
        digit = temp % 10;
        if (digit == 0) {
            isValid = 0;
            break;
        }
        sum += digit;
        temp /= 10;
    }

    if (isValid && sum % 9 == 0) {
        printf("%d is a Demlo number.\n", original);
    } else {
        printf("%d is not a Demlo number.\n", original);
    }
}

int main() {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    findDemloNumber(num);

    return EXIT_SUCCESS;
}