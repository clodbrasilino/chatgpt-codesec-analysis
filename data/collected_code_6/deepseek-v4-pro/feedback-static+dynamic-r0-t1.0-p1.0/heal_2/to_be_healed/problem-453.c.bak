#include <stdio.h>
#include <math.h>

int sum_even_factors(int n) {
    if (n <= 0) return 0;
    if (n % 2 != 0) return 0;

    int sum = 0;
    int temp = n;
    while (temp % 2 == 0) {
        sum += 2;
        temp /= 2;
    }
    if (temp == 1) {
        sum -= 2;
    } else {
        sum += 2;
    }

    int limit = (int)sqrt((double)n);
    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0) {
            int counterpart = n / i;
            if (counterpart != i && counterpart % 2 == 0) sum += counterpart;
        }
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 943247682 + 2121118182 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:14309,execs:6551,op:havoc,rep:7)
     * UBSan: signed integer overflow: 1158202962 + 2144395572 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:6112,execs:2713,op:havoc,rep:8)
     */
    if (n != 2) sum += n;
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