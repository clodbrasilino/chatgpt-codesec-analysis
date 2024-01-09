#include <stdio.h>

int findCubeSum(int n) {
    int sum = 0;
    int num = 1;
    
    for (int i = 0; i < n; i++) {
        sum += num * num * num;
        num += 2;
    }
    
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    
    int cubeSum = findCubeSum(n);
    printf("Cube sum of first %d odd natural numbers: %d\n", n, cubeSum);
    
    return 0;
}