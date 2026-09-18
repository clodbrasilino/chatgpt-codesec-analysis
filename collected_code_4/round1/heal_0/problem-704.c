#include<stdio.h>

double HarmonicSum(int n) {
    double harmonicSum = 0;

    if(n > 0) {
        for(int i = 1; i < n; i++) {
            harmonicSum += 1.0/i;
        }
    } 

    return harmonicSum;
}

int main() {
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    if(num <= 0) {
     printf("Please enter positive number\n");
     return 0;
    }

    double result = HarmonicSum(num);

    printf("The harmonic sum of first %d numbers is %f\n", num-1, result);

    return 0;
}