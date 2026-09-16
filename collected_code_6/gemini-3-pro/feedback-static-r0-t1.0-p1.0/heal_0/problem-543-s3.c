#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_digits(int num) {
    int count = 0;
    if (num == 0) {
        return 1;
    }
    if (num < 0) {
        if (num == INT_MIN) {
            num = INT_MAX; 
        } else {
            num = -num;
        }
    }
    while (num > 0) {
        count++;
        num /= 10;
    }
    return count;
}

void add_and_print_digits(int a, int b) {
    long long sum = (long long)a + (long long)b;
    
    int count = 0;
    long long temp = sum;
    
    if (temp == 0) {
        count = 1;
    } else {
        if (temp < 0) {
            temp = -temp;
        }
        while (temp > 0) {
            count++;
            temp /= 10;
        }
    }
    
    printf("%d\n", count);
}

int main(void) {
    int num1, num2;
    
    if (scanf("%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    add_and_print_digits(num1, num2);
    
    return EXIT_SUCCESS;
}