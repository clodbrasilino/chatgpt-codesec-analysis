#include<stdio.h>

int sum_of_fifth_power(int n) {
    int sum = 0;
    int num = 1;
    for (int i = 0; i < n; i++) {
        sum += num * num * num * num * num;
        num += 2;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    
    int result = sum_of_fifth_power(n);
    printf("The sum of the fifth power of the first %d even natural numbers is: %d\n", n, result);
    
    return 0;
}