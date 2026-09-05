#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int gcd(int a, int b)
{
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
}

int is_coprime(int a, int b)
{
    if (a == 0 && b == 0) {
        return 0;
    }
    
    return gcd(a, b) == 1;
}

int main(void)
{
    int num1, num2;
    
    printf("Enter two integers: ");
    
    if (scanf("%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (is_coprime(num1, num2)) {
        printf("%d and %d are co-prime\n", num1, num2);
    } else {
        printf("%d and %d are not co-prime\n", num1, num2);
    }
    
    return EXIT_SUCCESS;
}