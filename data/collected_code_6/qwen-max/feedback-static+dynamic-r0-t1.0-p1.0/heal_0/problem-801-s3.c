#include <stdio.h>

int countEqualNumbers(int a, int b, int c) {
    int count = 0;
    if (a == b) count++;
    if (a == c) count++;
    if (b == c && b != a) count += 2;
    return count;
}

int main() {
    int x, y, z;
    printf("Enter three integers: ");
    scanf("%d %d %d", &x, &y, &z);
    int result = countEqualNumbers(x, y, z);
    printf("Number of equal numbers: %d\n", result);
    return 0;
}