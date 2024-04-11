#include <stdio.h>

int checkOppositeSign(int a, int b) {
    return ((a ^ b) < 0);
}

int main() {
    int a = 10;
    int b = -20;

    if(checkOppositeSign(a, b)) {
        printf("Numbers have opposite signs\n");
    } else {
        printf("Numbers have same sign\n");
    }

    return 0;
}