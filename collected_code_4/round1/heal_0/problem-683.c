#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool isRepresentable(int num) {
    int squareRoot = sqrt(num);
    for (int i = 0; i <= squareRoot; i++) {
        for (int j = 0; j <= squareRoot; j++) {
            if (i * i + j * j == num) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int num;
    printf("Enter a number: \n");
    scanf("%d", &num);
    if (isRepresentable(num)) {
        printf("Yes, the number can be represented as sum of two squares.\n");
    } else {
        printf("No, the number can not be represented as sum of two squares.\n");
    }
    return 0;
}