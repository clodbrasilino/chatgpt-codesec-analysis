#include <stdio.h>

float averageOfOddNumbers(int n) {
    float sum = 0;
    int count = 0;
    for(int i = 1; i <= n; i += 2) {
        sum += i;
        ++count;
    }
    return (count > 0) ? sum/count : 0;
}

int main() {
    int n;
    printf("Enter a number:\n");
    scanf("%d", &n);
    if(n%2 != 0) {
        printf("The average of odd numbers till %d is %.2f\n", n, averageOfOddNumbers(n));
    } else {
        printf("Please provide an odd number\n");
    }
    return 0;
}