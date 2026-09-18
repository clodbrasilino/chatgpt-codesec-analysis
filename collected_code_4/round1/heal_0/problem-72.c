#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int check_difference_of_squares(int number) {
    int temp, root;
    if (number < 0)
        return -1;
    temp = number % 4;
    root = (int)sqrt(number);
    if ((temp == 2 && root * root == number) ||
        (number == 2 || number == 3))
        return 0;
    return 1;
}

int main() {
    int number;
    printf("Enter a number: \n");
    scanf("%d", &number);
    int result = check_difference_of_squares(number);
    switch(result) {
        case -1:
            printf("Negative numbers cannot be represent as difference of two squares.\n");
            break;
        case 0:
            printf("Number: %d can't be represented as difference of two squares.\n", number);
            break;
        case 1:
            printf("Number: %d can be represented as difference of two squares.\n", number);
            break;
        default:
            printf("Something went wrong.\n");
    }
    return 0;
}