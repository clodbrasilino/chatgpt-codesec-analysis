#include <stdio.h>

int bellNumber(int num) {
    int bell[num+1][num+1];
    bell[0][0] = 1;
    for (int i=1; i<=num; i++) {
        bell[i][0] = bell[i-1][i-1];
        for (int j=1; j<=i; j++) {
            bell[i][j] = bell[i-1][j-1] + bell[i][j-1];
        }
    }
    return bell[num][0];
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    printf("The %dth Bell number is %d\n", number, bellNumber(number));
    return 0;
}