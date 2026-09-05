#include <stdio.h>

int find_minimum(int first_number, int second_number);

int find_minimum(int first_number, int second_number)
{
    return (first_number < second_number) ? first_number : second_number;
}

int main(void)
{
    int number_one = 0;
    int number_two = 0;
    int minimum_value = 0;

    printf("Enter two integers: ");
    
    if (scanf("%d %d", &number_one, &number_two) != 2)
    {
        fprintf(stderr, "Invalid input provided.\n");
        return 1;
    }

    minimum_value = find_minimum(number_one, number_two);
    
    printf("Minimum: %d\n", minimum_value);

    return 0;
}