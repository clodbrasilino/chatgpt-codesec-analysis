#include <stdio.h>

int checkOppositeSigns(int x, int y) {
    return ((x ^ y) < 0);
}

int main() {
    int num1 = 100;
    int num2 = -100;
    if(checkOppositeSigns(num1, num2)) {
        printf("Numbers have opposite signs\n");
    } else {
        printf("Numbers don't have opposite signs\n");
    }
    return 0;
}