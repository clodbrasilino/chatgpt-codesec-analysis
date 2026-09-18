#include <stdio.h>

int cubeSum(int num) {
    int sum = 0;
    for(int i = 1; i <= num; i++) {
        sum += i * i * i;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number:\n");
    scanf("%d", &n);
    if(n < 1) {
        printf("Number must be greater than 0\n");
        return 1;
    }
    int sumOfCubes = cubeSum(n);
    printf("Sum of cubes: %d\n", sumOfCubes);
    return 0;
}