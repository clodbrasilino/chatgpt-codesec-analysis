#include <stdio.h>

int findNthNumber(int n, int m) {
    int count = 0;
    int num = 1;
    while(count < n) {
        if(num % m != 0) {
            count++;
        }
        num++;
    }
    return num - 1;
}

int main() {
    int n, m;
    printf("Enter the nth number: ");
    scanf("%d", &n);
    printf("Enter the number which should not be a multiple: ");
    scanf("%d", &m);
    int result = findNthNumber(n, m);
    printf("The %dth number in the sequence which is not a multiple of %d is: %d\n", n, m, result);
    return 0;
}