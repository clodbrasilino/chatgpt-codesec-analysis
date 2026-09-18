#include <stdio.h>

int sum_of_odd_numbers(int l, int r) {
    int sum = 0;
    for (int i = l; i <= r; i++) {
        if (i % 2 != 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int l, r;
    printf("Enter the range l and r: ");
    if(scanf("%d %d", &l, &r) != 2){
        printf ("Invalid input!\n");
        return 1;
    }

    int sum = sum_of_odd_numbers(l, r);
    printf("Sum of odd numbers in the range %d and %d is: %d\n", l, r, sum);

    return 0;
}