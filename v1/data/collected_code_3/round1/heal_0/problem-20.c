#include <stdio.h>
#include <math.h>

int isWoodall(int n) {
    double x = (log(n + 1) / log(2));
    return x == (int)x && (n & (n + 1)) == 0;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if(isWoodall(num))
        printf("%d is a Woodall number.\n", num);
    else
        printf("%d is not a Woodall number.\n", num);

    return 0;
}