#include <stdio.h>

long sum_of_cubes(int n) {
    long sum = 0;
    for (int i = 1; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4398046511104 * 2097152 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:982,execs:476,op:havoc,rep:13)
         * UBSan: signed integer overflow: 9223193340756366400 + 473384830201856 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:982,execs:476,op:havoc,rep:13)
         */
        sum += (long)i * i * i;
    }
    return sum;
}

long sum_of_numbers(int n) {
    long sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += i;
    }
    return sum;
}

long difference(int n) {
    long cubes_sum = sum_of_cubes(n);
    long numbers_sum = sum_of_numbers(n);
    return cubes_sum - numbers_sum;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    long diff = difference(n);
    printf("The difference is: %ld\n", diff);

    return 0;
}