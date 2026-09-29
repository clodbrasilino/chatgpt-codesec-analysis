#include <stdio.h>
#include <math.h>

int evenOddDivisor(int n) {
    int count = 0;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            if (n / i == i)
                count++;
            else 
                count += 2;
        }
    }
    if (count % 2 == 0)
        return 2;
    else 
        return 1; 
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    int result = evenOddDivisor(num);
    if (result == 2)
        printf("Even number of divisors\n");
    else
        printf("Odd number of divisors\n");

    return 0;
}