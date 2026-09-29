#include <stdio.h>
#include <stdlib.h>

int add_numbers(int a, int b) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -24394774 + -2125048854 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:1018,execs:501,op:havoc,rep:1)
     */
    return a + b;
}

int count_digits(int num) {
    int count = 0;
    if (num == 0) {
        return 1;
    }
    if (num < 0) {
        num = -num;
    }
    while (num > 0) {
        num /= 10;
        count++;
    }
    return count;
}

int main(void) {
    int a, b, sum, digits;
    
    printf("Enter two numbers: ");
    if (scanf("%d %d", &a, &b) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    sum = add_numbers(a, b);
    digits = count_digits(sum);
    
    printf("Sum: %d\n", sum);
    printf("Number of digits: %d\n", digits);
    
    return 0;
}