#include <stdio.h>
#include <math.h>

int isWoodall(int n) {
    double x = log2((double)n + 1);
    return x == (int)x && (int)x > 0;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if(isWoodall(num)) {
        printf("%d is a Woodall number.\n", num);
    } else {
        printf("%d is not a Woodall number.\n", num);
    }
    return 0;
}