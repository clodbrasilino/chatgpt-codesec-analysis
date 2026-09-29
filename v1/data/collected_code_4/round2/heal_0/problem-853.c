#include <stdio.h>
#include <stdlib.h>

int sumOfOddFactors(int num) {
    int sum = 0;
    for (int i = 1; i <= num; i++) {
        if (num % i == 0) {
            if(i % 2 != 0) {
                sum += i;
            }
        }
    }
    return sum;
}

int main() {
    int num;
    printf("Enter a number: ");
    if(scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input, expected an integer\n");
        exit(EXIT_FAILURE);
    }
    int sum = sumOfOddFactors(num);
    printf("Sum of odd factors of %d = %d\n", num, sum);
    return 0;
}