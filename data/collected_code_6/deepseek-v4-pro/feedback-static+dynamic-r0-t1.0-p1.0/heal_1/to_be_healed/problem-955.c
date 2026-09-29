#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_abundant(int n) {
    if (n <= 1) {
        return false;
    }
    
    int sum = 1;
    int sqrt_n = (int)sqrt((double)n);
    
    for (int i = 2; i <= sqrt_n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 1768518520 + 530555553 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:35112,execs:22820,op:havoc,rep:4)
                 * UBSan: signed integer overflow: 2037496703 + 175646265 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:25144,execs:16387,op:havoc,rep:2)
                 */
                sum += n / i;
            }
        }
    }
    
    return sum > n;
}

int main(void) {
    int num;
    
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (is_abundant(num)) {
        printf("%d is an abundant number\n", num);
    } else {
        printf("%d is not an abundant number\n", num);
    }
    
    return 0;
}