#include <stdio.h>

#define MAX_N 100

int newman_shanks_williams(int n) {
    if( n <= 0 ) {
        return 1;
    }
    int NSW[MAX_N + 1];

    NSW[0] = 1;
    NSW[1] = 1;
    for(int i = 2; i <= n; i++) {
        NSW[i] = 2 * NSW[i - 1] + NSW[i - 2];
    }
    return NSW[n];
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    if(n < 0 || n > MAX_N) {
        printf("Invalid input: Please enter a number between 0 and %d\n", MAX_N);
        return 1;
    }

    printf("The %dth Newman-Shanks-Williams number is: %d\n", n, newman_shanks_williams(n));
    return 0;
}