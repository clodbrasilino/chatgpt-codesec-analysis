#include <stdio.h>

long findLucasNumber(int n) {
    if (n < 0) {
        return -1;
    }

    long a = 2, b = 1;
    if (n == 0) return a;
    else if (n == 1) return b;

    long lucasNum;
    for (int i = 2; i <= n; i++) {
        lucasNum = a + b;
        a = b;
        b = lucasNum;
    }

    return lucasNum;
}

int main() {
    int nthLucasNum;
    printf("Enter a position for the Lucas number sequence: ");
    scanf("%d", &nthLucasNum);

    long lucasNum = findLucasNumber(nthLucasNum);
    if (lucasNum == -1) {
        printf("Error: Invalid position\n");
    } else {
        printf("The %dth Lucas number is %ld\n", nthLucasNum, lucasNum);
    }

    return 0;
}