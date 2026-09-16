#include <stdio.h>
#include <stdlib.h>

int is_even(int number)
{
    return (number & 1) == 0;
}

int main(void)
{
    int number = 0;
    int result = 0;

    printf("Enter an integer: ");
    result = scanf("%d", &number);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (is_even(number)) {
        printf("%d is even\n", number);
    } else {
        printf("%d is odd\n", number);
    }

    return EXIT_SUCCESS;
}