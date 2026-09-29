#include <stdio.h>

int lastTwoDigitsOfFactorial(int n) {
    int res = 1;
    for (int i = 1; i <= n; i++) {
        res = (res * i) % 100;
    }
    return res;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Last two digits of factorial: %02d\n", lastTwoDigitsOfFactorial(num));
    return 0;
}