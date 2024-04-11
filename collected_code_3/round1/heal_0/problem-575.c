#include <stdio.h>

int findNthNonMultiple(int n, int x) {
    int count = 0;
    int num = 1;
    while (1) {
        if (num % x != 0) {
            count++;
        }
        if (count == n) {
            return num;
        }
        num++;
    }
}

int main() {
    int n, x;
    printf("Enter the position of the number in the sequence: ");
    scanf("%d", &n);
    printf("Enter the number which should not be a multiple: ");
    scanf("%d", &x);
    int result = findNthNonMultiple(n, x);
    printf("The %dth number in the sequence which is not a multiple of %d is %d\n", n, x, result);
    return 0;
}