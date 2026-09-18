#include <stdio.h>

int calculate_sum(int n) {
    int sum = 0;
    while(n > 0) {
        sum += n;
        n -= 2;
    }
    return sum;
}


int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    if(n < 0) {
        printf("Input should be a positive integer.\n");
        return 1;
    }

    int sum = calculate_sum(n);
    printf("Sum is %d \n", sum);

    return 0;
}