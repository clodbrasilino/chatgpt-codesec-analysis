#include <stdio.h>

int carolNumber(int n) {
    int result = 0;
    for (int i = 1; i <= n; i++) {
        result = result + (i * i + i);
    }
    return result;
}

int main() {
    int n = 0;
    printf("Enter the value of n: ");
    if(scanf("%d", &n) != 1) {
        printf("Invalid entry.\n");
        return -1;
    }
    printf("The %d'th Carol number is: %d\n", n, carolNumber(n));
    return 0;
}