#include <stdio.h>

int isInfiniteSequence(int number) {
    int current = 1;

    while (1) {
        if (current == number) {
            return 1;
        }

        current *= 2;
    }

    return 0;
}

int main() {
    int number;

    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'number' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &number);

    if (isInfiniteSequence(number)) {
        printf("The number %d is present in the infinite sequence.\n", number);
    } else {
        printf("The number %d is not present in the infinite sequence.\n", number);
    }

    return 0;
}