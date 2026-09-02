#include <stdio.h>
#include <math.h>

int countDigits(int n) {
    int count = 0;
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}

int isArmstrong(int num) {
    /* Possible weaknesses found:
     *  temp is initialized
     */
    int n = 0, result = 0, temp = num;
    /* Possible weaknesses found:
     *  temp is overwritten
     *  Redundant initialization for 'temp'. The initialized value is overwritten before it is read. [redundantInitialization]
     */
    for (temp = num; temp != 0; temp /= 10) {
        n++;
    }

    temp = num;
    while (temp != 0) {
        int remainder = temp % 10;
        result += pow(remainder, n);
        temp /= 10;
    }

    return (result == num);
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    if (isArmstrong(number)) {
        printf("%d is an Armstrong number.\n", number);
    } else {
        printf("%d is not an Armstrong number.\n", number);
    }

    return 0;
}