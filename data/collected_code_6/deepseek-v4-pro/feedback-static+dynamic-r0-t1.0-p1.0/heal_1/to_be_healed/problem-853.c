#include <stdio.h>
#include <math.h>

int sum_of_odd_factors(int n) {
    int sum = 0;
    int limit = (int)sqrt((double)n);
    
    for (int i = 1; i <= limit; i++) {
        if (n % i == 0) {
            if (i % 2 == 1) {
                sum += i;
            }
            
            int paired_factor = n / i;
            if (paired_factor != i && paired_factor % 2 == 1) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 1654463533 + 551487843 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:1384,execs:902,op:havoc,rep:3)
                 */
                sum += paired_factor;
            }
        }
    }
    
    return sum;
}

int main(void) {
    int number;
    
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1 || number <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    
    int result = sum_of_odd_factors(number);
    printf("Sum of odd factors: %d\n", result);
    
    return 0;
}