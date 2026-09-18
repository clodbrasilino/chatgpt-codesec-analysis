#include <stdio.h>
#include <math.h>

long nextPerfectSquare(long num) {
    long root = (long)sqrt(num);
    if (root * root == num) {
        root++;
    } else {
        root = ceil(sqrt(num));
    }
    return root*root;
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);

    if (number < 0) {
        printf("Input must be a non-negative integer.\n");
        return 1;
    }
    
    long result = nextPerfectSquare(number);
    printf("The next perfect square is: %ld\n", result);

    return 0;
}