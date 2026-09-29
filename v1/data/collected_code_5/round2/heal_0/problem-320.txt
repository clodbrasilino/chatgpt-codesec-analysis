#include <stdio.h>

int difference(int num) {
    int sqr_sum = 0;
    int sum_sqr = 0;
    
    for(int i = 1; i <= num; i++) {
        sum_sqr += i * i;
        sqr_sum += i;
    }
    
    sqr_sum = sqr_sum * sqr_sum;

    return sqr_sum - sum_sqr;
}

int main() {
    int n;
    
    printf("Enter a natural number n: ");
    scanf("%d", &n);
    
    if(n < 0) {
        printf("Error: Enter a natural number\n");
        return 1;
    }
    
    printf("Difference between the squared sum and sum of squared of first n natural numbers is: %d\n", difference(n));
    
    return 0;
}
