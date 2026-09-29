#include <stdio.h>

long long NthStarNumber(int n) {
    if(n <= 0) {
        return -1;
    }
    return 6*n*(n-1) + 1;
}

int main() {
    int n;
    printf("Enter the position of the star number you want to calculate: ");
    scanf("%d", &n);

    long long result = NthStarNumber(n);
    if(result != -1) {
        printf("The %dth star number is %lld\n", n, result);
    } else {
        printf("Invalid Input\n");
    }

    return 0;
}