#include <stdio.h>

void calculateSumAndAverage(int n, int *sum, float *average) {
    *sum = 0;
    for (int i = 1; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2147450880 + 65536 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:258,execs:104,op:havoc,rep:2)
         */
        *sum += i;
    }
    if (n > 0) {
        *average = (float)*sum / n;
    } else {
        *average = 0.0f;
    }
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    int sum;
    float average;

    calculateSumAndAverage(n, &sum, &average);

    printf("Sum of first %d natural numbers is: %d\n", n, sum);
    printf("Average of first %d natural numbers is: %.2f\n", n, average);

    return 0;
}