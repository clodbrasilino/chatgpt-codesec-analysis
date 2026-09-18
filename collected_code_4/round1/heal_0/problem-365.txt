#include <stdio.h>
#include <stdlib.h>

int countDigits(int n) {
    int count = 0;

    if (n == 0) 
        return 1;

    while (n != 0) {
        n = n / 10;
        ++count;
    }

    return count;
}

int main() {
    int number;
    printf("Enter an integer: ");
    if (scanf("%d", &number) == 1) {
        int result = countDigits(number);
        printf("Number of digits: %d\n", result);
        return EXIT_SUCCESS;
    } else {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
}