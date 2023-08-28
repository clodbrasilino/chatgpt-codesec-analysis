#include <stdio.h>

int findSumOfOddNumbers(int l, int r) {
    int sum = 0;
    
    // swap l and r if l is greater than r
    if (l > r) {
        int temp = l;
        l = r;
        r = temp;
    }
    
    // loop through the range and add odd numbers to the sum
    for (int i = l; i <= r; i++) {
        if (i % 2 != 0) {
            sum += i;
        }
    }
    
    return sum;
}

int main() {
    int l, r;
    
    // getting inputs for range l and r
    printf("Enter the range l and r: ");
    scanf("%d %d", &l, &r);
    
    // call the function to find the sum of odd numbers
    int sum = findSumOfOddNumbers(l, r);
    
    // print the result
    printf("The sum of odd natural numbers between %d and %d is %d\n", l, r, sum);
    
    return 0;
}