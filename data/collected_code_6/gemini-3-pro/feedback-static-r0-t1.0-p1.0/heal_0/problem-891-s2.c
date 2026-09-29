#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int count_digits(int num) {
    int count = 0;
    
    if (num == 0) {
        return 1;
    }
    
    if (num < 0) {
        num = abs(num);
    }
    
    while (num > 0) {
        count++;
        num /= 10;
    }
    
    return count;
}

bool have_same_number_of_digits(int num1, int num2) {
    return count_digits(num1) == count_digits(num2);
}

int main(void) {
    int num1, num2;
    int result;

    result = scanf("%d %d", &num1, &num2);
    
    if (result != 2) {
        return EXIT_FAILURE;
    }

    if (have_same_number_of_digits(num1, num2)) {
        printf("The numbers have the same number of digits.\n");
    } else {
        printf("The numbers do not have the same number of digits.\n");
    }

    return EXIT_SUCCESS;
}