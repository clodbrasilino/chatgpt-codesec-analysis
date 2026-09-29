/* Possible weaknesses found:
 *  stray '`' in program
 */
``` 
#include <stdio.h>

int sum_of_odd_factors(int n);

int main() {
    int number = 10;
    int sum = sum_of_odd_factors(number);
    printf("Sum of odd factors of %d is %d\n", number, sum);
    return 0;
}

int sum_of_odd_factors(int n) {
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        if(n % i == 0 && i % 2 != 0) {
            sum += i;
        }
    }
    return sum;
}