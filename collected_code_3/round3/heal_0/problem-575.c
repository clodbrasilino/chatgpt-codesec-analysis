#include <stdio.h>

int findNthNonMultiple(int n, int num) {
    int count = 0;
    int i = 1;
    while (1) {
        if (i % num != 0) {
            count++;
            if (count == n) {
                return i;
            }
        }
        i++;
    }
}

int main() {
    int n, num;
    printf("Enter the position of the number in the sequence: ");
    scanf("%d", &n);
    printf("Enter the number which should not be a multiple: ");
    scanf("%d", &num);
    int result = findNthNonMultiple(n, num);
    printf("The %dth number in the sequence which is not a multiple of %d is %d\n", n, num, result);
    return 0;
}