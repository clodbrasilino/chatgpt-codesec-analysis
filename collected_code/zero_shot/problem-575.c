#include <stdio.h>
#include <stdbool.h>

int nthNotMultiple(int n, int num) {
    int count = 0, i = 1;
    while (count < n) {
        if (i % num != 0) {
            count++;
        }
        i++;
    }
    return i - 1;
}

int main() {
    int n, num;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("Enter the number: ");
    scanf("%d", &num);

    int result = nthNotMultiple(n, num);
    printf("The %dth number not multiple of %d is: %d\n", n, num, result);

    return 0;
}