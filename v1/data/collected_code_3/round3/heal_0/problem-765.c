#include <stdio.h>

int findNthPolite(int n) {
    int count = 0;
    int num = 1;
    while (1) {
        int temp = num;
        while (temp) {
            if (temp & 1 && !(temp & 2)) {
                count++;
                if (count == n) {
                    return num;
                }
                break;
            }
            temp = temp >> 1;
        }
        num++;
    }
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("The %dth polite number is: %d\n", n, findNthPolite(n));
    return 0;
}