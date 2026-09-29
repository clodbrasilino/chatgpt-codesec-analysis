#include <stdio.h>
#include <math.h>

int sumEvenFactors(int n) {
    if (n <= 0) {
        return 0;
    }

    int sum = 0;
    int limit = (int)sqrt((double)n);

    for (int i = 1; i <= limit; i++) {
        if (n % i == 0) {
            if (i % 2 == 0) {
                sum += i;
            }
            int counterpart = n / i;
            if (counterpart != i && counterpart % 2 == 0) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 2143543798 + 32517350 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000002,time:19768,execs:9820,op:havoc,rep:4)
                 * UBSan: signed integer overflow: 2033030002 + 1016515000 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:7368,execs:3713,op:havoc,rep:2)
                 * UBSan: signed integer overflow: 2014763816 + 671587938 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:4205,execs:2133,op:havoc,rep:3)
                 */
                sum += counterpart;
            }
        }
    }

    return sum;
}

int main(void) {
    int number;

    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    int result = sumEvenFactors(number);
    printf("Sum of even factors: %d\n", result);

    return 0;
}