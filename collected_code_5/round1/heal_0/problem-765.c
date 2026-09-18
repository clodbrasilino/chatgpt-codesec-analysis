#include <stdio.h>
#include <stdlib.h>

int polite_number(int n) {
    int count = 0;
    int current_num = 0;

    while(count < n) {
       current_num++;
       // check if the number is not power of 2, since power of 2 only has one way of summation 
       // and hence is not polite number.
       if (current_num & (current_num - 1)) {
           count++;
       }
    }
    
    return current_num;
}

int main() {
    int nth;
    printf("Enter the nth polite number to find:\n");
    if(scanf("%d", &nth) != 1) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    if(nth < 1) {
        printf("Invalid input, n should be greater than 0.\n");
        return EXIT_FAILURE;
    }

    int result = polite_number(nth);
    printf("%dth polite number is %d\n", nth, result);

    return 0;
}