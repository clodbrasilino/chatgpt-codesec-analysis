#include <stdio.h>

int have_same_number_of_digits(int a, int b) {
    int count_a = 0, count_b = 0;
    
    if (a == 0) count_a = 1;
    else {
        if (a < 0) a = -a;
        while (a > 0) {
            a /= 10;
            count_a++;
        }
    }
    
    if (b == 0) count_b = 1;
    else {
        if (b < 0) b = -b;
        while (b > 0) {
            b /= 10;
            count_b++;
        }
    }
    
    return count_a == count_b;
}

int main(void) {
    int num1, num2;
    
    printf("Enter two integers: ");
    if (scanf("%d %d", &num1, &num2) != 2) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (have_same_number_of_digits(num1, num2)) {
        printf("The numbers have the same number of digits.\n");
    } else {
        printf("The numbers have different number of digits.\n");
    }
    
    return 0;
}