#include <stdio.h>
#include <math.h>

int is_perfect_square(int n) {
    int root = (int)sqrt(n);
    return n == root * root;
}

int main() {
    int num;

    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        return 1;
    }

    if (is_perfect_square(num)) {
        printf("The square root of %d is %d\n", num, (int)sqrt(num));
    } else {
        printf("%d is not a perfect square\n", num);
    }

    return 0;
}