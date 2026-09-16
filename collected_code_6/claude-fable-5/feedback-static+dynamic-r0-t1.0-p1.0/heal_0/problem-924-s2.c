#include <stdio.h>
#include <stdlib.h>

int max_of_two(int a, int b);

int max_of_two(int a, int b)
{
    return (a > b) ? a : b;
}

int main(void)
{
    int num1;
    int num2;
    int result;

    printf("Enter first number: ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Error: invalid input for first number\n");
        return EXIT_FAILURE;
    }

    printf("Enter second number: ");
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Error: invalid input for second number\n");
        return EXIT_FAILURE;
    }

    result = max_of_two(num1, num2);

    printf("Maximum: %d\n", result);

    return EXIT_SUCCESS;
}