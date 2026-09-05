#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

int find_perfect_square_root(int num) {
    if (num < 0) {
        return -1;
    }
    
    int root = (int)sqrt((double)num);
    
    if (root * root == num) {
        return root;
    }
    
    return -1;
}

int main() {
    int number;
    
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    int result = find_perfect_square_root(number);
    
    if (result == -1) {
        printf("%d is not a perfect square\n", number);
    } else {
        printf("Square root of %d is %d\n", number, result);
    }
    
    return 0;
}