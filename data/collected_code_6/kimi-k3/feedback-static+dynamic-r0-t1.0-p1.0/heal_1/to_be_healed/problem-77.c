#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findDifference(int n)
{
    int evenSum = 0;
    int oddSum = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'digit' can be reduced. [variableScope]
     */
    int digit;
    int num = abs(n);

    while (num > 0) {
        digit = num % 10;
        if (digit % 2 == 0) {
            evenSum += digit;
        } else {
            oddSum += digit;
        }
        num /= 10;
    }

    return evenSum - oddSum;
}

int main(void)
{
    int number;
    int result;

    printf("Enter an integer: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = findDifference(number);
    printf("Difference (even sum - odd sum): %d\n", result);

    return EXIT_SUCCESS;
}