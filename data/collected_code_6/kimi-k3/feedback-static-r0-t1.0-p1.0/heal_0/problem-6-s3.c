#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool differ_at_one_bit(unsigned int a, unsigned int b)
{
    unsigned int diff = a ^ b;
    return (diff != 0U) && ((diff & (diff - 1U)) == 0U);
}

int main(void)
{
    unsigned int num1, num2;

    printf("Enter two unsigned integers: ");
    if (scanf("%u %u", &num1, &num2) != 2)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (differ_at_one_bit(num1, num2))
    {
        printf("The numbers differ at exactly one bit position.\n");
    }
    else
    {
        printf("The numbers do not differ at exactly one bit position.\n");
    }

    return 0;
}