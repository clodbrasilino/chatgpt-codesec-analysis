#include <stdio.h>
#include <stdlib.h>

int count_digits(int num) {
    int count = 0;
    if (num == 0) {
        return 1;
    }
    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}

int add_and_count_digits(int a, int b) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1095008906 + 1385770634 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:1217,execs:641,op:havoc,rep:3)
     */
    int sum = a + b;
    int digits = count_digits(abs(sum));
    printf("Sum: %d\n", sum);
    printf("Number of digits: %d\n", digits);
    return sum;
}

int main(void) {
    int num1, num2;
    
    printf("Enter first number: ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter second number: ");
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    add_and_count_digits(num1, num2);
    
    return EXIT_SUCCESS;
}