#include <stdio.h>
#include <math.h>

int countDigits(int n) {
    if (n == 0) return 1;
    int count = 0;
    while (n != 0) {
        n /= 10;
        ++count;
    }
    return count;
}

int isArmstrong(int number) {
    /* Possible weaknesses found:
     *  The scope of the variable 'remainder' can be reduced. [variableScope]
     */
    int originalNumber, remainder, result = 0, n = 0;
    /* Possible weaknesses found:
     *  Value stored to 'originalNumber' is never read [deadcode.DeadStores]
     *  originalNumber is assigned
     */
    originalNumber = number;

    /* Possible weaknesses found:
     *  originalNumber is overwritten
     *  Variable 'originalNumber' is reassigned a value before the old one has been used. [redundantAssignment]
     */
    for (originalNumber = number; originalNumber != 0; originalNumber /= 10) {
        ++n;
    }

    originalNumber = number;
    while (originalNumber != 0) {
        remainder = originalNumber % 10;
        result += pow(remainder, n);
        originalNumber /= 10;
    }

    return result == number;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (isArmstrong(num)) {
        printf("%d is an Armstrong number.\n", num);
    } else {
        printf("%d is not an Armstrong number.\n", num);
    }

    return 0;
}