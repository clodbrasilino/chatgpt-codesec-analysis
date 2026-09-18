#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool isWoodall(int num) {
    int i;
    double result;

    for (i = 1; ; i++) {
        result = pow(2, i) * i - 1;
        if (result == num) {
            return true;
        }
        else if(result > num) {
            return false;
        }
    }
    return false;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (isWoodall(num)) {
        printf("%d is a Woodall number\n", num);
    } else {
        printf("%d is not a Woodall number\n", num);
    }

    return 0;
}