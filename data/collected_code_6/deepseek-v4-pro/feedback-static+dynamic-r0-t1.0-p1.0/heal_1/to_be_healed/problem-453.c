#include <stdio.h>
#include <math.h>

int sum_even_factors(int n) {
    if (n <= 0) return 0;
    /* Possible weaknesses found:
     *  Assuming that condition 'n%2!=0' is not redundant
     */
    if (n % 2 != 0) return 0;

    int sum = 0;
    int temp = n;
    while (temp % 2 == 0) {
        sum += 2;
        temp /= 2;
    }
    sum += 2 * (temp == 1 ? 0 : 1);

    int limit = (int)sqrt((double)n);
    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0) {
            if (i % 2 == 0) sum += i;
            int counterpart = n / i;
            if (counterpart != i && counterpart % 2 == 0) sum += counterpart;
        }
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 965371290 + 1842981546 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:11700,execs:5252,op:havoc,rep:6)
     * UBSan: signed integer overflow: 815762480 + 1579388472 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000011,time:45263,execs:20203,op:havoc,rep:2)
     *  Condition 'n%2==0' is always true [knownConditionTrueFalse]
     *  Condition 'n%2==0' is always true
     */
    if (n % 2 == 0 && n != 2) sum += n;
    return sum;
}

int main(void) {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    printf("Sum of even factors: %d\n", sum_even_factors(number));
    return 0;
}