#include <stdio.h>
#include <math.h>

int countDivisors(int n) {
    int count = 0;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            if (n / i == i)
                count++;
            else
                count += 2;
        }
    }
    return count;
}

int isEven(int n) {
    return n % 2 == 0;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    int count = countDivisors(num);
    if (isEven(count)) {
        printf("Count of divisors is even.\n");
    } else {
        printf("Count of divisors is odd.\n");
    }
    return 0;
}