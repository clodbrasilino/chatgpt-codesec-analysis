#include <stdio.h>

int lucasNumber(int n)
{
    if (n == 0)
        return 2;
    else if (n == 1)
        return 1;
    else
        return lucasNumber(n - 1) + lucasNumber(n - 2);
}

int main()
{
    int n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    
    int result = lucasNumber(n);
    printf("The %d'th Lucas number is: %d", n, result);
    
    return 0;
}