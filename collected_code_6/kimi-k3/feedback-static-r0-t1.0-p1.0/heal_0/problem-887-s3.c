#include <stdio.h>

int is_odd(int number)
{
    return (number & 1) != 0;
}

int main(void)
{
    int number;
    int result;

    printf("Enter an integer: ");
    result = scanf("%d", &number);

    if (result != 1)
    {
        printf("Invalid input\n");
        return 1;
    }

    if (is_odd(number))
    {
        printf("%d is odd\n", number);
    }
    else
    {
        printf("%d is even\n", number);
    }

    return 0;
}