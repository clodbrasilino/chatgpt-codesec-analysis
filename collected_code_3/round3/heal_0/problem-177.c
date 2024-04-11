#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void findNumbers(int low, int high) {
    int i, j;
    for (i = low; i <= high; i++) {
        for (j = i + 1; j <= high; j++) {
            if ((i * j) / gcd(i, j) <= high) {
                printf("Numbers are: %d and %d\n", i, j);
                return;
            }
        }
    }
    printf("No such numbers found\n");
}

int main() {
    int low, high;
    printf("Enter the lower limit: ");
    scanf("%d", &low);
    printf("Enter the upper limit: ");
    scanf("%d", &high);
    findNumbers(low, high);
    return 0;
}