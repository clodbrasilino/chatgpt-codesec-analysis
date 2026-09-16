#include <stdio.h>
#include <stdbool.h>

bool isEven(int number);

bool isEven(int number)
{
    return (number % 2 == 0);
}

int main(void)
{
    int number = 0;

    printf("Enter a number: ");
    if (scanf("%d", &number) != 1)
    {
        fprintf(stderr, "Error: Invalid input.\n");
        return 1;
    }

    if (isEven(number))
    {
        printf("%d is even.\n", number);
    }
    else
    {
        printf("%d is odd.\n", number);
    }

    return 0;
}