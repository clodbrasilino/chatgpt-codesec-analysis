#include <stdio.h>
#include <stdlib.h>

int is_abundant(int n) {
    if (n <= 0) {
        return 0;
    }
    
    int sum = 0;
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    
    return sum > n;
}

int main(void) {
    int num;
    
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (is_abundant(num)) {
        printf("%d is an abundant number\n", num);
    } else {
        printf("%d is not an abundant number\n", num);
    }
    
    return EXIT_SUCCESS;
}