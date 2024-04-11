#include <stdio.h>

float averageOfOdds(int n) {
    int sum = 0;
    int count = 0;
    for(int i = 1; i <= n; i += 2) {
        sum += i;
        count++;
    }
    return (float)sum / count;
}

int main() {
    int n;
    printf("Enter an odd number: ");
    scanf("%d", &n);
    if(n % 2 == 0) {
        printf("Please enter an odd number.\n");
        return 1;
    }
    float average = averageOfOdds(n);
    printf("The average of odd numbers till %d is %.2f\n", n, average);
    return 0;
}