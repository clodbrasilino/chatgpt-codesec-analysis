#include <stdio.h>

int isInfiniteSequence(int number) {
    int current = 1;

    while (current <= number) {
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

    if(scanf("%d", &number) != 1) {
        printf("Invalid input!\n");
        return -1;
    }

    if (isInfiniteSequence(number)) {
        printf("The number %d is present in the infinite sequence.\n", number);
    } else {
        printf("The number %d is not present in the infinite sequence.\n", number);
    }

    return 0;
}