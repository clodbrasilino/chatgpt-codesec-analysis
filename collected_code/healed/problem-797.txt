#include <stdio.h>

int findSumOfOddNumbers(int l, int r) {
    
    int sum = 0;
    
    if (l > r) {
        int temp = l;
        l = r;
        r = temp;
    }
    
    for (int i = l; i <= r; i++) {
        if (i % 2 != 0) {
            sum += i;
        }
    }
    
    return sum;
}

int main() {
    
    int l = 0, r = 0;
    
    printf("Enter the range l and r: ");
    scanf("%d %d", &l, &r);
    
    int sum = findSumOfOddNumbers(l, r);
    
    printf("The sum of odd natural numbers between %d and %d is %d\n", l, r, sum);
    
    return 0;
}