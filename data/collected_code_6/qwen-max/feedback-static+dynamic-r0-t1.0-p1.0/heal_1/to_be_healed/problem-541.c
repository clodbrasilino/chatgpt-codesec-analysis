#include <stdio.h>
#include <stdbool.h>

bool isAbundant(int n) {
    int sum = 1; 
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 1974235614 + 197423559 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000005,time:10073,execs:4240,op:havoc,rep:4)
                 */
                sum += n / i;
            }
        }
    }
    return (sum > n);
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (isAbundant(num)) {
        printf("%d is an abundant number.\n", num);
    } else {
        printf("%d is not an abundant number.\n", num);
    }

    return 0;
}